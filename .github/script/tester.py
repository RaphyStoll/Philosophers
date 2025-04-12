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
RESET = "\033[0m"
BOLD = "\033[1m"

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
    print(f"{BOLD}{BLUE}==> Démarrage du script tester.py{RESET}")
    report_path = LOG_DIR / "report.txt"
    with open(report_path, "w") as report:
        report.write("==== PHILOSOPHERS CI REPORT ====\n")
        # Compilation
        print(f"{CYAN}⏳ Compilation en cours...{RESET}")
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
            print(f"{CYAN}🔎 Analyse norminette...{RESET}")
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
            print(f"{CYAN}🧪 Lancement des tests...{RESET}")
            write_header(report, "TESTS")
            report.write("running test_runner ...\n")
            result = run_cmd("./philo/test_runner", log_path=LOG_DIR / "tests.txt")
            with open(LOG_DIR / "tests.txt") as test_log:
                report.writelines(test_log.readlines())

            # Valgrind
            print(f"{CYAN}🧼 Vérification mémoire avec Valgrind...{RESET}")
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
        print(f"{BLUE}📋 Compilation du résumé...{RESET}")
        write_header(report, "RESUMER")
        if compilation_failed:
            report.write("Tests non exécutés (compilation échouée)\n")
        else:
            with open(LOG_DIR / "tests.txt") as test_log:
                for line in test_log:
                    if "[TEST" in line:
                        report.write(line)

    print(f"\n{BOLD}{GREEN}==== RÉSUMÉ CONSOLE ===={RESET}")
    print(report_path.read_text())


if __name__ == "__main__":
    main()
