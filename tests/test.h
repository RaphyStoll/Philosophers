#define RUN_SUBTEST(name, func) do { \
	printf("----- %s -----", name); \
	int result = func(); \
	printf("result: %s\n", result ? "OK" : "KO"); \
	failures += !result; \
} while (0)