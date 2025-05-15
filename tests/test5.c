/* ************************************************************************** */
/*                                                                            */
/*                           Test File - test: is_flag                         */
/*                                                                            */
/*   Created: 2025/05/11 22:26:31                                             */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "test.h"
#include "../header/struct.h"

bool	is_flag(t_flags *flags, char *str);

static int	base_test(void)
{
	bool result = true;
	t_flags flags = {0};

	// Cas valide : --
	if (!is_flag(&flags, "--debug"))
	{
		printf(" > FAIL: is_flag(\"--debug\")\n");
		result = false;
	}
	if (!is_flag(&flags, "--verbose"))
	{
		printf(" > FAIL: is_flag(\"--verbose\")\n");
		result = false;
	}
	if (!is_flag(&flags, "--animate"))
	{
		printf(" > FAIL: is_flag(\"--animate\")\n");
		result = false;
	}
	if (!is_flag(&flags, "--stats"))
	{
		printf(" > FAIL: is_flag(\"--stats\")\n");
		result = false;
	}
	if (!is_flag(&flags, "--log"))
	{
		printf(" > FAIL: is_flag(\"--log\")\n");
		result = false;
	}
	return (!result);
}

static int	base_test2(void)
{
	bool result = true;
	t_flags flags = {0};

	// Cas valide : -
	if (!is_flag(&flags, "-d"))
	{
		printf(" > FAIL: is_flag(\"-d\")\n");
		result = false;
	}
	if (!is_flag(&flags, "-v"))
	{
		printf(" > FAIL: is_flag(\"-v\")\n");
		result = false;
	}
	if (!is_flag(&flags, "-a"))
	{
		printf(" > FAIL: is_flag(\"-a\")\n");
		result = false;
	}
	if (!is_flag(&flags, "-s"))
	{
		printf(" > FAIL: is_flag(\"-s\")\n");
		result = false;
	}
	if (!is_flag(&flags, "-l"))
	{
		printf(" > FAIL: is_flag(\"-l\")\n");
		result = false;
	}
	return (!result);
}

static int	fail_test(void)
{
	bool result = true;
	t_flags flags = {0};

	if (is_flag(&flags, "--unknow"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"--unknow\")\n");
	}
	if (is_flag(&flags, "--"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"--\")\n");
	}
	if (is_flag(&flags, "dsajkfhasduk"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"dsajkfhasduk\")\n");
	}
	return (!result);
}

static int	fail_test2(void)
{
	bool result = true;
	t_flags flags = {0};

	if (is_flag(&flags, "-u"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"-u\")\n");
	}
	if (is_flag(&flags, ""))
	{
		result = false;
		printf(" > FAIL: is_flag(\"""\")\n");
	}
	if (is_flag(&flags, " "))
	{
		result = false;
		printf(" > FAIL: is_flag(\"" "\")\n");
	}
	if (is_flag(&flags, "\n"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"\\n\")\n");
	}
	if (is_flag(&flags, "\t"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"\\t\")\n");
	}
	if (is_flag(&flags, "\r"))
	{
		result = false;
		printf(" > FAIL: is_flag(\"\\r\")\n");
	}
	return (!result);
}

static int	null_param_test(void)
{
	bool result = true;

	// test avec flags = NULL
	if (is_flag(NULL, "--debug"))
	{
		printf(" > FAIL: is_flag(NULL, \"--help\") should not succeed (may segfault)\n");
		result = false;
	}

	// test avec str = NULL
	t_flags flags = {0};
	if (is_flag(&flags, NULL))
	{
		printf(" > FAIL: is_flag(&flags, NULL) should return false or handle NULL\n");
		result = false;
	}

	return (!result);
}

static int	help_base_test(void)
{
	bool result = true;
	const char *tmp_path = "tmp_help.log";
	int saved_stdout = dup(STDOUT_FILENO);
	int fd = open(tmp_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);

	int display_fail = 0;
	t_flags flags = {0};

	if (!is_flag(&flags, "--help"))
	{
		display_fail = 1;
		PL();
		result = false;
	}
	if (flags.help != true)
	{
		display_fail = 2;
		PL();
		result = false;
	}
	if (!is_flag(&flags, "-h"))
	{
		display_fail = 3;
		PL();
		result = false;
	}
	if (flags.help != true)
	{
		display_fail = 4;
		PL();
		result = false;
	}

	fflush(stdout);
	close(fd);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	unlink(tmp_path);

	switch (display_fail)
	{
		case 0:
			break;
		case 1:
			printf(" > FAIL: is_flag(\"--help\")\n");
			break;
		case 2:
			printf(" > FAIL: [--help] flags.help not set to true\n");
			break;
		case 3:
			printf(" > FAIL: is_flag(\"-h\")\n");
			break;
		case 4:
			printf(" > FAIL: [-h] flags.help not set to true\n");
			break;
	}
	return (!result);
}

int test5(void)
{
	int failures = 0;

	RUN_SUBTEST("base_test [help]", help_base_test);
	RUN_SUBTEST("base_test [--]", base_test);
	RUN_SUBTEST("base_test [-]", base_test2);
	RUN_SUBTEST("fail_test [--]", fail_test);
	RUN_SUBTEST("fail_test [-]", fail_test2);
	RUN_SUBTEST("null_param_test", null_param_test);

	return (failures);
}