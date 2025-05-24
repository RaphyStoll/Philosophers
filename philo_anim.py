#!/usr/bin/env python3
import sys
import time
import re
import os

# Nombre de philosophes (à détecter)
NB_PHILO = 0
states = {}

# Emojis pour les états
EMOJIS = {
    "is eating": "🍝",
    "is sleeping": "💤",
    "is thinking": "🤔",
    "has taken a fork": "🍴",
    "died": "💀",
}


def clear():
    os.system("cls" if os.name == "nt" else "clear")


def render():
    clear()
    print("┌" + "─" * 40 + "┐")
    print("│ Visualisation des philosophes │")
    print("└" + "─" * 40 + "┘\n")
    for i in range(1, NB_PHILO + 1):
        state = states.get(i, "")
        print(f"Philo {i:>2}: {state}")
    print("\nAppuyez sur Ctrl+C pour quitter.")


def update(line):
    match = re.match(r"(\d+)\s+(\d+)\s(.+)", line)
    if not match:
        return
    time_ms, pid, action = int(match[1]), int(match[2]), match[3]

    emoji = EMOJIS.get(action.strip(), "")
    if emoji:
        if action.strip() == "has taken a fork":
            # On empile les forks
            current = states.get(pid, "")
            states[pid] = current + emoji
        else:
            states[pid] = emoji + " " + action.strip()

    render()


def main():
    global NB_PHILO
    try:
        first_line = sys.stdin.readline()
        if not first_line:
            return
        sys.stdout.write(first_line)
        sys.stdout.flush()
        match = re.match(r"(\d+)\s+(\d+)\s(.+)", first_line)
        if match:
            NB_PHILO = max(NB_PHILO, int(match[2]))
            update(first_line)
        for line in sys.stdin:
            match = re.match(r"\d+\s+(\d+)\s(.+)", line)
            if match:
                NB_PHILO = max(NB_PHILO, int(match[1]))
            update(line)
            time.sleep(0.05)
    except KeyboardInterrupt:
        clear()
        print("Animation terminée.")
        sys.exit(0)


if __name__ == "__main__":
    main()
