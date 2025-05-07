#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *str);

int test_strlen_case(const char *input)
{
    size_t expected = strlen(input);
    size_t actual = ft_strlen(input);
    if (expected != actual)
    {
        fprintf(stderr, "FAIL: ft_strlen(\"%s\") = %zu (expected %zu)\n", input, actual, expected);
        return 1;
    }
    return 0;
}

int test2(void)
{
    int fails = 0;

    fails += test_strlen_case("");
    fails += test_strlen_case("a");
    fails += test_strlen_case("abc");
    fails += test_strlen_case("Hello World!");
    fails += test_strlen_case("   ");
    fails += test_strlen_case("\n\t\r");
    fails += test_strlen_case("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

    if (fails == 0)
    {
        write(1, "All ft_strlen tests passed.\n", 29);
        return 0;
    }
    else
    {
        fprintf(stderr, "%d test(s) failed.\n", fails);
        return 1;
    }
}