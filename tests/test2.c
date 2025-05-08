#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

size_t	ft_strlen(const char *str);

int test_strlen_case(const char *input, const char *label)
{
	size_t expected = strlen(input);
	size_t actual = ft_strlen(input);
	if (expected != actual)
	{
		fprintf(stderr, "FAIL [%s]: ft_strlen(\"%s\") = %zu (expected %zu)\n",
			label, input, actual, expected);
		return 1;
	}
	return 0;
}

int test_empty_string(void)
{
	return test_strlen_case("", "empty");
}
int test_single_char(void)       
{
	return test_strlen_case("a", "single char");
}

int test_short_string(void)      
{
	return test_strlen_case("abc", "short string");
}

int test_hello_world(void)       
{
	return test_strlen_case("Hello World!", "Hello World!");
}

int test_spaces_only(void)       
{
	return test_strlen_case("   ", "spaces only");
}

int test_escaped_chars(void)     
{
	return test_strlen_case("\n\t\r", "escaped chars");
}

int test_long_text(void)         
{
	return test_strlen_case("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", "long text");
}

int test2(void)
{
	
	int failures = 0;

	RUN_SUBTEST("test_empty_string", test_empty_string);
	RUN_SUBTEST("test_single_char", test_single_char);
	RUN_SUBTEST("test_short_string", test_short_string);
	RUN_SUBTEST("test_hello_world", test_hello_world);
	RUN_SUBTEST("test_spaces_only", test_spaces_only);
	RUN_SUBTEST("test_escaped_chars", test_escaped_chars);
	RUN_SUBTEST("test_long_text", test_long_text);
	
	return (failures);
}