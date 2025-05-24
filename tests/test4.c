/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: ft_strcmp                      */
/*                                                                            */
/*   Created: 2025/05/11 21:49:28                                             */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "test.h"

int	ft_strcmp(char *s1, char *s2);

static int test_strcmp_case(const char *s1, const char *s2, const char *label)
{
	int expected = strcmp(s1, s2);
	int result = ft_strcmp((char *)s1, (char *)s2);
	if ((expected == 0 && result != 0) || (expected < 0 && result >= 0) || (expected > 0 && result <= 0))
	{
		fprintf(stderr, " > FAIL: [%s] ft_strcmp(\"%s\", \"%s\") = %d (expected sign %d)\n",
			label, s1, s2, result, expected);
		return (!1);
	}
	return (!0);
}

static int test_strcmp_equal_strings(void)
{
	return test_strcmp_case("abc", "abc", "equal strings");
}

static int test_strcmp_empty_strings(void)
{
	return test_strcmp_case("", "", "empty strings");
}

static int test_strcmp_nonempty_vs_empty(void)
{
	return test_strcmp_case("abc", "", "non-empty vs empty");
}

static int test_strcmp_empty_vs_nonempty(void)
{
	return test_strcmp_case("", "abc", "empty vs non-empty");
}

static int test_strcmp_diff_last_char(void)
{
	return test_strcmp_case("abc", "abd", "diff last char");
}

static int test_strcmp_diff_last_char_inv(void)
{
	return test_strcmp_case("abc", "abb", "diff last char inverted");
}

static int test_strcmp_completely_different(void)
{
	return test_strcmp_case("abc", "xyz", "completely different");
}

static int test_strcmp_long_equal_strings(void)
{
	return test_strcmp_case("long test string", "long test string", "long equal strings");
}

int test4(void)
{
	
	int failures = 0;

	RUN_SUBTEST("test_strcmp_equal_strings", test_strcmp_equal_strings);
	RUN_SUBTEST("test_strcmp_empty_strings", test_strcmp_empty_strings);
	RUN_SUBTEST("test_strcmp_nonempty_vs_empty", test_strcmp_nonempty_vs_empty);
	RUN_SUBTEST("test_strcmp_empty_vs_nonempty", test_strcmp_empty_vs_nonempty);
	RUN_SUBTEST("test_strcmp_diff_last_char", test_strcmp_diff_last_char);
	RUN_SUBTEST("test_strcmp_diff_last_char_inv", test_strcmp_diff_last_char_inv);
	RUN_SUBTEST("test_strcmp_completely_different", test_strcmp_completely_different);
	RUN_SUBTEST("test_strcmp_long_equal_strings", test_strcmp_long_equal_strings);
	
	return (failures);
}