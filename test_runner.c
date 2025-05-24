#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "tests/test.h"

int test1(void);  // structure t_data
int test2(void);  // ft_strlen
int test3(void);  // error_msg
int test4(void);  // ft_strcmp
int test6(void);  // parsing arguments
int test7(void);  // time functions
int test8(void);  // philosopher creation
int test9(void);  // simulation edge cases
int test10(void); // print and status functions

typedef struct s_test {
	const char *name;
	int (*func)(void);
} t_test;

t_test tests[] = {
    { "[test init] structure t_data", test1 },
	{ "[test utils] ft_strlen", test2 },
	{ "[test utils] error_msg", test3 },
	{ "[test utils] ft_strcmp", test4},
	{ "[test parsing] argument validation", test6},
	{ "[test time] time functions", test7},
	{ "[test init] philosopher creation", test8},
	{ "[test simulation] edge cases", test9},
	{ "[test output] print and status", test10},
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
		fprintf(log_file, "===== %s =====\n\n", tests[i].name);
		fflush(log_file);
		int stdout_copy = dup(fileno(stdout));
		int stderr_copy = dup(fileno(stderr));
		dup2(fileno(log_file), fileno(stdout));
		dup2(fileno(log_file), fileno(stderr));
		fflush(stderr);
		
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
		const char *status = res == 0 ? "[OK] → 🟢" : "[KO] → 🔴";
		fprintf(log_file, "%d. %s %s (%.2fs)\n\n", i + 1, tests[i].name, status, duration);
		if (res != 0)
			failed = 1;	
	}
	fflush(log_file);
	fclose(log_file);	
	return failed;
}