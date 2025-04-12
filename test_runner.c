#include <stdio.h>
#include "colors.h"

// Déclarations des fonctions de test
int test1(void);
int test_example2(void);

// Structure pour mapper nom <-> fonction
typedef struct s_test {
	const char *name;
	int (*func)(void);
} t_test;

int main(void) {
	t_test tests[] = {
		{ "test1", test1 },
		{ NULL, NULL }
	};

	for (int i = 0; tests[i].name != NULL; ++i) {
		printf(BOLD CYAN "→ Running test %d...%s\n" RESET, i + 1, "");
		printf(YELLOW "Test name: %s\n" RESET, tests[i].name);
		int res = tests[i].func();
		printf(LIGHT_BLUE "valgrind\n" RESET);
		printf("[TEST %d] [%s%s%s]\n\n",
			i + 1,
			res == 0 ? GREEN : RED,
			res == 0 ? "OK" : "KO",
			RESET);
	}
	return 0;
}
