#!/usr/bin/env python3
import subprocess
import time
import re

PHILO_PATH = "./output/philo"  # Chemin vers votre binaire

TESTS = [
    {
        "desc": "1 philo meurt sans manger",
        "args": ["1", "800", "200", "200"],
        "expect_death": True,
    },
    {
        "desc": "5 philosophes, personne ne meurt",
        "args": ["5", "800", "200", "200"],
        "expect_death": False,
    },
    {
        "desc": "5 philosophes, chacun mange 7 fois",
        "args": ["5", "800", "200", "200", "7"],
        "expect_death": False,
        "expect_meals": 7,
    },
    {
        "desc": "4 philosophes, personne ne meurt",
        "args": ["4", "410", "200", "200"],
        "expect_death": False,
    },
    {
        "desc": "4 philosophes, 1 meurt",
        "args": ["4", "310", "200", "100"],
        "expect_death": True,
    },
]


def run_philo(args):
    try:
        proc = subprocess.run(
            [PHILO_PATH] + args, capture_output=True, text=True, timeout=10
        )
        return proc.stdout.strip().split("\n")
    except subprocess.TimeoutExpired:
        return ["ERROR: Timeout"]


def analyze_output(lines, args, expect_death, expect_meals=None):
    death_detected = any("died" in line for line in lines)
    if expect_death and not death_detected:
        return False, "❌ Philosopher should have died but didn’t."
    if not expect_death and death_detected:
        return False, "❌ Philosopher died unexpectedly."

    if expect_meals is not None:
        meals = {}
        for line in lines:
            match = re.match(r"\d+ (\d+) is eating", line)
            if match:
                pid = int(match.group(1))
                meals[pid] = meals.get(pid, 0) + 1
        if all(count >= expect_meals for count in meals.values()) and len(meals) == int(
            args[0]
        ):
            return True, "✅ All philosophers ate at least 7 times."
        return False, f"❌ Not all philosophers ate {expect_meals} times. {meals}"
    return True, "✅ Passed."


def main():
    print("=== PHILO TESTER ===\n")
    for test in TESTS:
        print(f"Test: {test['desc']}")
        output = run_philo(test["args"])
        ook, msg = analyze_output(
            output, test["args"], test["expect_death"], test.get("expect_meals")
        )
        print(msg)
        print("-" * 50)
        time.sleep(1)


if __name__ == "__main__":
    main()
