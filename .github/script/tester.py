import subprocess
import os
from pathlib import Path
import requests
import platform
import shlex

# Couleurs (inspirées de colors.h)
RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"
LIGHT_RED = "\033[1;91m"
LIGHT_GREEN = "\033[1;92m"
LIGHT_BLUE = "\033[1;94m"
LIGHT_WHITE = "\033[1;97m"
RESET = "\033[0m"
BOLD = "\033[1m"
WHITE = "\033[0;37m"

SEPARATOR = f"{LIGHT_BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{RESET}"

LOG_DIR = Path("logs")
LOG_DIR.mkdir(exist_ok=True)

try:
    REPO_ROOT = Path(
        subprocess.run(
            "git rev-parse --show-toplevel",
            shell=True,
            capture_output=True,
            text=True,
            check=True,
        ).stdout.strip()
    )
except subprocess.CalledProcessError:
    REPO_ROOT = Path(__file__).resolve().parents[2]


def write_header(f, title):
    f.write(f"\n==== {title.upper()} ====\n")


def run_cmd(cmd, log_path=None, timeout=30):
    system = platform.system()
    if "timeout" not in cmd:
        if system == "Linux":
            cmd = f"timeout {timeout}s {cmd}"
        elif system == "Darwin":
            cmd = f"gtimeout {timeout}s {cmd}"  # brew install coreutils

    try:
        result = subprocess.run(
            cmd,
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            cwd=REPO_ROOT,
            timeout=timeout,
        )
    except subprocess.TimeoutExpired as e:
        if log_path:
            with open(log_path, "w") as f:
                f.write(f"[TIMEOUT] Commande interrompue après {timeout} secondes\n")
                if e.stdout:
                    f.write(e.stdout)
                if e.stderr:
                    f.write(e.stderr)
        result = subprocess.CompletedProcess(
            cmd, returncode=124, stdout="[TIMEOUT]", stderr=str(e)
        )
    return result


def parse_test_results(test_log_path):
    """Parse les résultats des tests et retourne (ok_count, ko_count, failed_tests)"""
    ok_count = 0
    ko_count = 0
    failed_tests = []

    if not test_log_path.exists():
        return 0, 0, ["Test log file not found"]

    with open(test_log_path, "r") as f:
        content = f.read()
        lines = content.split("\n")

        current_test = None
        for line in lines:
            if "[test" in line and "] " in line:
                # Extrait le nom du test: "[test utils] ft_strlen"
                current_test = line.strip()
            elif "[OK] → 🟢" in line:
                ok_count += 1
            elif "[KO] → 🔴" in line:
                ko_count += 1
                if current_test:
                    # Cherche les détails d'erreur pour ce test
                    failed_tests.append(current_test)

    return ok_count, ko_count, failed_tests


def parse_report_status(report_path):
    """Parse le rapport et retourne le statut de chaque section"""
    status = {
        "compilation": "unknown",
        "norminette": "unknown",
        "tests": "unknown",
        "valgrind": "unknown",
        "compilation_errors": "",
        "norminette_errors": "",
        "test_details": "",
        "failed_tests": [],
    }

    if not report_path.exists():
        return status

    with open(report_path, "r") as f:
        content = f.read()
        sections = content.split("====")

        for section in sections:
            if "COMPILATION" in section:
                if "[OK]" in section:
                    status["compilation"] = "ok"
                elif "[KO]" in section:
                    status["compilation"] = "ko"
                    # Extraction des erreurs de compilation
                    lines = section.split("\n")
                    error_lines = [
                        line.strip()
                        for line in lines
                        if "error:" in line or "Error" in line
                    ]
                    status["compilation_errors"] = "\n".join(
                        error_lines[:5]
                    )  # Max 5 lignes

            elif "NORMINETTE" in section:
                if "[OK]" in section:
                    status["norminette"] = "ok"
                elif "[KO]" in section:
                    status["norminette"] = "ko"
                    # Extraction des erreurs norminette
                    lines = section.split("\n")
                    error_lines = [line.strip() for line in lines if "Error" in line]
                    status["norminette_errors"] = "\n".join(
                        error_lines[:5]
                    )  # Max 5 lignes

            elif "VALGRIND" in section:
                if "[OK]" in section:
                    status["valgrind"] = "ok"
                elif "[KO]" in section:
                    status["valgrind"] = "ko"

    # Parse des résultats de tests
    test_log_path = LOG_DIR / "tests.txt"
    ok_count, ko_count, failed_tests = parse_test_results(test_log_path)

    if ko_count == 0 and ok_count > 0:
        status["tests"] = "ok"
    elif ko_count > 0:
        status["tests"] = "ko"
        status["failed_tests"] = failed_tests
        status["test_details"] = f"{ok_count} OK, {ko_count} KO"

    return status


def create_discord_embed(report_path, commit_hash, commit_msg):
    """Crée l'embed Discord au format JSON"""

    status = parse_report_status(report_path)

    # Détermine la couleur globale (vert si tout OK, rouge sinon)
    all_ok = all(
        s == "ok"
        for s in [
            status["compilation"],
            status["norminette"],
            status["tests"],
            status["valgrind"],
        ]
    )
    color = 0x00FF00 if all_ok else 0xFF0000  # Vert ou Rouge

    # Création des fields
    fields = [
        {
            "name": "📦 Compilation",
            "value": "🟢 OK" if status["compilation"] == "ok" else "🔴 FAILED",
            "inline": True,
        },
        {
            "name": "🔎 Norminette",
            "value": "🟢 OK" if status["norminette"] == "ok" else "🔴 ERRORS",
            "inline": True,
        },
        {
            "name": "🧪 Tests",
            "value": (
                f"🟢 {status['test_details']}"
                if status["tests"] == "ok"
                else f"🔴 {status['test_details']}"
            ),
            "inline": True,
        },
        {
            "name": "🧼 Valgrind",
            "value": "🟢 CLEAN" if status["valgrind"] == "ok" else "🔴 LEAKS DETECTED",
            "inline": True,
        },
    ]

    # Ajout du résumé et des détails d'erreur si nécessaire
    if not all_ok:
        failed_sections = []
        if status["compilation"] == "ko":
            failed_sections.append("Compilation")
        if status["norminette"] == "ko":
            failed_sections.append("Norminette")
        if status["tests"] == "ko":
            failed_sections.append("Tests")
        if status["valgrind"] == "ko":
            failed_sections.append("Valgrind")

        # Résumé des échecs
        fields.append(
            {
                "name": "❌ Failed sections",
                "value": ", ".join(failed_sections),
                "inline": False,
            }
        )

        # Détails des erreurs (sauf Valgrind)
        if status["compilation"] == "ko" and status["compilation_errors"]:
            fields.append(
                {
                    "name": "🔧 Compilation Errors",
                    "value": f"```\n{status['compilation_errors']}\n```",
                    "inline": False,
                }
            )

        if status["norminette"] == "ko" and status["norminette_errors"]:
            fields.append(
                {
                    "name": "🔍 Norminette Errors",
                    "value": f"```\n{status['norminette_errors']}\n```",
                    "inline": False,
                }
            )

        if status["tests"] == "ko" and status["failed_tests"]:
            test_failures = "\n".join(status["failed_tests"][:3])  # Max 3 tests
            fields.append(
                {
                    "name": "🧪 Test Failures",
                    "value": f"```\n{test_failures}\n```",
                    "inline": False,
                }
            )

        if status["valgrind"] == "ko":
            fields.append(
                {
                    "name": "🧼 Memory Analysis",
                    "value": "Check CI logs for detailed memory analysis",
                    "inline": False,
                }
            )
    else:
        fields.append(
            {"name": "✅ Status", "value": "All checks passed", "inline": False}
        )

    # Construction de l'embed
    embed = {
        "title": "🌿 Philosophers CI Report",
        "description": f"**Commit:** `{commit_hash}`\n{commit_msg}",
        "color": color,
        "fields": fields,
        "footer": {"text": "Philosophers CI Pipeline"},
        "timestamp": subprocess.run(
            ["date", "-Iseconds"], capture_output=True, text=True
        ).stdout.strip(),
    }

    return {"embeds": [embed]}


def build_discord_report(report_path):
    """Version legacy pour compatibilité (garde l'ancien format texte)"""
    lines = []
    section = None
    with open(report_path) as f:
        for line in f:
            line = line.strip()
            line = line.replace("[OK]", "🟢 [OK]").replace("[KO]", "🔴 [KO]")
            if line.startswith("===="):
                section = line.strip("= ").upper()
                if section == "PHILOSOPHERS CI REPORT":
                    lines.append("🌿 **PHILOSOPHERS CI REPORT**")
                elif section == "COMPILATION":
                    lines.append("\n📦 **COMPILATION**")
                elif section == "NORMINETTE":
                    lines.append("\n🔎 **NORMINETTE**")
                elif section == "TESTS":
                    lines.append("\n🧪 **TESTS**")
                elif section == "VALGRIND":
                    lines.append("\n🧼 **VALGRIND**")
                elif section == "REMARQUES":
                    lines.append("\n📌 **REMARQUES**")
                elif section == "RESUMER":
                    lines.append("\n📊 **RÉSUMÉ**")
            elif line:
                lines.append(line)
    return "\n".join(lines)


def main():
    print(f"{SEPARATOR}")
    commit_hash = run_cmd("git rev-parse --short HEAD", timeout=30).stdout.strip()
    commit_msg = run_cmd("git log -1 --pretty=%B", timeout=30).stdout.strip()
    print(f"{WHITE}📌 Commit : {commit_hash} - {commit_msg}{RESET}")
    print(f"{BOLD}{LIGHT_WHITE}🚀  Lancement du script tester.py{RESET}")
    print(f"{SEPARATOR}")
    report_path = LOG_DIR / "report.txt"
    with open(report_path, "w") as report:
        report.write(f"Commit : {commit_hash} - {commit_msg}\n")
        report.write("==== PHILOSOPHERS CI REPORT ====\n")
        # Compilation
        print(f"\n{CYAN}🔧 Étape 1 : Compilation...{RESET}")
        write_header(report, "COMPILATION")
        compilation_failed = False
        result = run_cmd("make test_runner", log_path=LOG_DIR / "build.txt", timeout=30)
        if result.returncode != 0:
            report.write("[KO]\n")
            write_header(report, "REMARQUES")
            report.write("Erreur de compilation :\n")
            report.write(result.stdout + result.stderr)
            compilation_failed = True
        else:
            report.write("[OK]\n")

        # Norminette
        if not compilation_failed:
            print(f"\n{CYAN}🔍 Étape 2 : Norminette...{RESET}")
            write_header(report, "NORMINETTE")
            result = run_cmd(
                f"norminette \"{REPO_ROOT / 'sources'}\"",
                log_path=LOG_DIR / "norm.txt",
                timeout=30,
            )
            if "Error" in result.stdout or "Error" in result.stderr:
                report.write("[KO]\n")
                write_header(report, "REMARQUES")
                report.write("Erreurs norminette :\n")
                report.write(result.stdout + result.stderr)
            else:
                report.write("[OK]\n")

            # Tests
            print(f"\n{CYAN}🧪 Étape 3 : Exécution des tests...{RESET}")
            write_header(report, "TESTS")
            report.write("running test_runner ...\n")
            test_log_path = LOG_DIR / "tests.txt"
            result = run_cmd("./test_runner", log_path=test_log_path, timeout=30)
            if result.returncode != 0:
                print(
                    f"{RED}❌ test_runner a échoué avec le code de retour {result.returncode}{RESET}"
                )
                if result.returncode == -6:
                    print(f"{RED}💥 Abort signal (SIGABRT, code -6){RESET}")
                if result.returncode == 134:
                    print(
                        f"{RED}💥 Abort signal (code 134) — possible double free, assert ou abort(){RESET}"
                    )
                elif result.returncode == 139:
                    print(f"{RED}💥 Segmentation fault (code 139){RESET}")
                elif result.returncode == 124:
                    print(f"{RED}⏱ Timeout (code 124){RESET}")
            if test_log_path.exists():
                with open(test_log_path) as test_log:
                    report.writelines(test_log.readlines())
            else:
                report.write("[KO]\n")
                write_header(report, "REMARQUES")
                report.write("Le fichier tests.txt n'a pas été généré.\n")
                report.write("stderr test_runner:\n")
                report.write(result.stderr)
                report.write("\nstdout test_runner:\n")
                report.write(result.stdout)

            # Valgrind
            print(f"\n{CYAN}🧼 Étape 4 : Vérification mémoire (Valgrind)...{RESET}")
            write_header(report, "VALGRIND")
            system = platform.system()
            runner_path = REPO_ROOT / "test_runner"
            escaped_runner_path = shlex.quote(str(runner_path))
            valgrind_cmd = f"leaks -atExit -- {escaped_runner_path}"
            if system == "Darwin":
                valgrind_cmd = f"leaks -atExit -- {escaped_runner_path}"
            else:
                valgrind_cmd = f"valgrind --leak-check=full --error-exitcode=1 {escaped_runner_path}"

            result = run_cmd(
                valgrind_cmd, log_path=LOG_DIR / "valgrind.txt", timeout=30
            )
            if result.returncode == 0:
                report.write("[OK]\n")
            else:
                report.write("[KO]\n")
                write_header(report, "REMARQUES")
                report.write("Fuites mémoire détectées :\n")
                valgrind_log_path = LOG_DIR / "valgrind.txt"
            if valgrind_log_path.exists():
                with open(valgrind_log_path, "r") as val_log:
                    report.writelines(val_log.readlines())
            else:
                report.write("Fichier valgrind.txt non généré.\n")
                report.write(f"stderr: {result.stderr}\n")

        # Résumé
        print(f"\n{CYAN}📋 Étape 5 : Génération du rapport...{RESET}")
        write_header(report, "RESUMER")
        ok_count = 0
        ko_count = 0
        if compilation_failed:
            report.write("Tests non exécutés (compilation échouée)\n")
        else:
            test_log_path = LOG_DIR / "tests.txt"
            if test_log_path.exists():
                with open(test_log_path) as test_log:
                    for line in test_log:
                        if "[TEST" in line:
                            report.write(line)
                        elif "[OK]" in line:
                            print(f"{BOLD}{GREEN}[OK]{RESET}")
                            ok_count += 1
                        elif "[KO]" in line:
                            print(f"{BOLD}{RED}[KO]{RESET}")
                            ko_count += 1
            else:
                print(
                    f"{YELLOW}⚠️  Le fichier tests.txt est manquant pour le résumé.{RESET}"
                )

    print(f"\n{SEPARATOR}")
    print(f"{BOLD}{LIGHT_WHITE}📊  RÉSUMÉ CONSOLE{RESET}")
    print(f"{SEPARATOR}")
    print(SEPARATOR)
    print(
        f"{BOLD}✅ Tests réussis : {GREEN}{ok_count} OK{RESET}  ❌ Échecs : {RED}{ko_count} KO{RESET}"
    )
    print(SEPARATOR)

    print(f"\n{SEPARATOR}")
    print(f"{BOLD}{LIGHT_WHITE}📄  DÉTAIL DU RAPPORT{RESET}")
    print(f"{SEPARATOR}")

    section = None
    with open(report_path) as f:
        for line in f:
            line = line.strip()
            if line.startswith("===="):
                section = line.strip("= ").upper()
                if section == "COMPILATION":
                    print(f"\n{CYAN}📦 COMPILATION :{RESET}")
                elif section == "NORMINETTE":
                    print(f"\n{CYAN}🔎 NORMINETTE :{RESET}")
                elif section == "TESTS":
                    print(f"\n{CYAN}🧪 TESTS :{RESET}")
                elif section == "VALGRIND":
                    print(f"\n{CYAN}🧼 VALGRIND :{RESET}")
                elif section == "REMARQUES":
                    print(f"\n{YELLOW}📌 REMARQUES :{RESET}")
                elif section == "RESUMER":
                    print(f"\n{SEPARATOR}")
            elif "[OK]" in line:
                print(f"{BOLD}{GREEN}[OK]{RESET}")
            elif "[KO]" in line:
                print(f"{BOLD}{RED}[KO]{RESET}")
            elif "[TEST" in line:
                print(f"{WHITE}{line}{RESET}")
            elif line:
                print(line)

    webhook = os.getenv("DISCORD_WEBHOOK")
    if not webhook:
        print(
            f"{YELLOW}⚠️  Aucun webhook Discord détecté. Le rapport ne sera pas envoyé.{RESET}"
        )
        return
    else:
        print(f"{CYAN}📡 Webhook Discord détecté : {webhook}{RESET}")

    if webhook:
        print(f"\n{CYAN}📡 Envoi du rapport vers Discord...{RESET}")

        # Création de l'embed JSON
        payload = create_discord_embed(report_path, commit_hash, commit_msg)

        try:
            response = requests.post(webhook, json=payload)
            if response.status_code == 204:
                print(f"{GREEN}✅ Rapport envoyé avec succès (embed format) !{RESET}")
            else:
                print(
                    f"{RED}❌ Échec de l'envoi Discord (embed) : {response.status_code}{RESET}"
                )
                # Fallback vers l'ancien format
                print(f"{YELLOW}⚠️ Tentative avec l'ancien format...{RESET}")
                fallback_payload = {"content": build_discord_report(report_path)}
                response = requests.post(webhook, json=fallback_payload)
                if response.status_code == 204:
                    print(f"{GREEN}✅ Rapport envoyé (format texte) !{RESET}")
                else:
                    print(
                        f"{RED}❌ Échec total de l'envoi Discord : {response.status_code}{RESET}"
                    )
        except Exception as e:
            print(f"{RED}❌ Exception Discord : {e}{RESET}")


if __name__ == "__main__":
    main()
