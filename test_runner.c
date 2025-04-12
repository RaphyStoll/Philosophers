#include <stdio.h>

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
		printf("running test %d ....\n", i + 1);
		printf("test %s\n", tests[i].name);
		int res = tests[i].func();
		printf("valgrind\n");
		printf("[TEST %d] [%s]\n\n", i + 1, res == 0 ? "OK" : "KO");
	}
	return 0;
}
