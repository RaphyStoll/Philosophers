#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int test1(void);

typedef struct s_test {
	const char *name;
	int (*func)(void);
} t_test;

int main(void) {
	t_test tests[] = {
		{ "test1", test1 },
		{ NULL, NULL }
	};

	FILE *log_file = fopen("logs/tests.txt", "w");
	if (!log_file) {
		perror("Erreur ouverture logs/tests.txt");
		return 1;
	}

	int failed = 0;
	for (int i = 0; tests[i].name != NULL; ++i) {
		clock_t start = clock();
		int res = tests[i].func();
		clock_t end = clock();
		double duration = (double)(end - start) / CLOCKS_PER_SEC;
		fprintf(log_file, "[TEST %d] %s [%s] (%.2fs)\n", i + 1, tests[i].name,
			res == 0 ? "OK" : "KO", duration);
		if (res != 0)
			failed = 1;
	}

	fclose(log_file);
	return failed;
}
