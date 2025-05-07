#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int test1(void);
int test2(void);
int test3(void);
int test4(void);

typedef struct s_test {
	const char *name;
	int (*func)(void);
} t_test;

t_test tests[] = {
    { "[test init] structure t_data", test1 },
	{ "[test utils] ft_strlen", test2 } ,
	{ "[test utils] error_msg", test3 },
    { NULL, NULL }
};

int main(void) {
	system("mkdir -p logs");
	FILE *log_file = fopen("logs/tests.txt", "w");
	if (!log_file) {
		perror("Erreur ouverture logs/tests.txt");
		return 1;
	}

	int failed = 0;
	for (int i = 0; tests[i].name != NULL; ++i) {
		fprintf(log_file, "===== %s =====\n", tests[i].name);
		fflush(log_file);

		int stdout_copy = dup(fileno(stdout));
		int stderr_copy = dup(fileno(stderr));
		dup2(fileno(log_file), fileno(stdout));
		dup2(fileno(log_file), fileno(stderr));

		clock_t start = clock();
		int res = tests[i].func();
		clock_t end = clock();

		fflush(stdout);
		fflush(stderr);
		dup2(stdout_copy, fileno(stdout));
		dup2(stderr_copy, fileno(stderr));
		close(stdout_copy);
		close(stderr_copy);

		double duration = (double)(end - start) / CLOCKS_PER_SEC;
		fprintf(log_file, "%d. %s [%s] (%.2fs)\n\n", i + 1, tests[i].name,
			res == 0 ? "OK" : "KO", duration);
		if (res != 0)
			failed = 1;
	}

	fclose(log_file);
	return failed;
}
