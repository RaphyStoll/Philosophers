#ifndef TEST_H
# define TEST_H

# include <stdio.h>

# define RUN_SUBTEST(name, func) do { \
		printf("----- %s -----\n", name); \
		int result = func(); \
		printf("result: %s\n\n", result ? "OK" : "KO"); \
		failures += !result; \
	} while (0)

# define PL() printf("→ %s:%d\n", __FILE__, __LINE__)

#endif