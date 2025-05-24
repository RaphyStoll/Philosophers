#ifndef TEST_H
# define TEST_H

# include <stdio.h>

# define RED = "\033[0;31m"
# define GREEN = "\033[0;32m"
# define YELLOW = "\033[0;33m"
# define BLUE = "\033[0;34m"
# define CYAN = "\033[0;36m"
# define LIGHT_RED = "\033[1;91m"
# define LIGHT_GREEN = "\033[1;92m"
# define LIGHT_BLUE = "\033[1;94m"
# define LIGHT_WHITE = "\033[1;97m"
# define RESET = "\033[0m"
# define BOLD = "\033[1m"
# define WHITE = "\033[0;37m"

// CORRECTION ICI: inversion de la logique d'affichage
# define RUN_SUBTEST(name, func) do { \
		printf("----- %s -----\n", name); \
		int result = func(); \
		printf("result: %s\n\n", result ? "OK 🟢" : "KO 🔴"); \
		failures += !result; \
	} while (0)

# define PL() printf("→ %s:%d\n", __FILE__, __LINE__)

#endif