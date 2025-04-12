import subprocess
import os
from pathlib import Path

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
    print("==> Démarrage du script tester.py")
    report_path = LOG_DIR / "report.txt"
    with open(report_path, "w") as report:
        report.write("==== PHILOSOPHERS CI REPORT ====\n")
        # Compilation
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
            write_header(report, "TESTS")
            report.write("running test_runner ...\n")
            result = run_cmd("./philo/test_runner", log_path=LOG_DIR / "tests.txt")
            with open(LOG_DIR / "tests.txt") as test_log:
                report.writelines(test_log.readlines())

            # Valgrind
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
        write_header(report, "RESUMER")
        if compilation_failed:
            report.write("Tests non exécutés (compilation échouée)\n")
        else:
            with open(LOG_DIR / "tests.txt") as test_log:
                for line in test_log:
                    if "[TEST" in line:
                        report.write(line)

    print("\n==== RÉSUMÉ CONSOLE ====")
    print(report_path.read_text())


if __name__ == "__main__":
    main()
