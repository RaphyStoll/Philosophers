import subprocess
import os
from pathlib import Path

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

SEPARATOR = f"{LIGHT_BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━{RESET}"

LOG_DIR = Path("logs")
LOG_DIR.mkdir(exist_ok=True)


def write_header(f, title):
    f.write(f"\n==== {title.upper()} ====\n")


def run_cmd(cmd, log_path=None):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if log_path:
        with open(log_path, "w") as f:
            f.write(result.stdout + result.stderr)
    return result


def main():
    print(f"{SEPARATOR}")
    print(f"{BOLD}{LIGHT_WHITE}🚀  Lancement du script tester.py{RESET}")
    print(f"{SEPARATOR}")
    report_path = LOG_DIR / "report.txt"
    with open(report_path, "w") as report:
        report.write("==== PHILOSOPHERS CI REPORT ====\n")
        # Compilation
        print(f"\n{CYAN}🔧 Étape 1 : Compilation...{RESET}")
        write_header(report, "COMPILATION")
        compilation_failed = False
        result = run_cmd("make test -C philo", log_path=LOG_DIR / "build.txt")
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
            result = run_cmd("norminette philo", log_path=LOG_DIR / "norm.txt")
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
            result = run_cmd("./philo/test_runner", log_path=LOG_DIR / "tests.txt")
            with open(LOG_DIR / "tests.txt") as test_log:
                report.writelines(test_log.readlines())

            # Valgrind
            print(f"\n{CYAN}🧼 Étape 4 : Vérification mémoire (Valgrind)...{RESET}")
            write_header(report, "VALGRIND")
            result = run_cmd(
                "valgrind --leak-check=full --error-exitcode=1 ./philo/test_runner",
                log_path=LOG_DIR / "valgrind.txt",
            )
            if result.returncode == 0:
                report.write("[OK]\n")
            else:
                report.write("[KO]\n")
                write_header(report, "REMARQUES")
                report.write("Fuites mémoire détectées :\n")
                with open(LOG_DIR / "valgrind.txt") as val_log:
                    report.writelines(val_log.readlines())

        # Résumé
        print(f"\n{CYAN}📋 Étape 5 : Génération du rapport...{RESET}")
        write_header(report, "RESUMER")
        ok_count = 0
        ko_count = 0
        if compilation_failed:
            report.write("Tests non exécutés (compilation échouée)\n")
        else:
            with open(LOG_DIR / "tests.txt") as test_log:
                for line in test_log:
                    if "[TEST" in line:
                        report.write(line)
                    elif "[OK]" in line:
                        print(f"{BOLD}{GREEN}[OK]{RESET}")
                        ok_count += 1
                    elif "[KO]" in line:
                        print(f"{BOLD}{RED}[KO]{RESET}")
                        ko_count += 1

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


if __name__ == "__main__":
    main()
