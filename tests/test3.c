#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int error_msg(const char *msg);

int test_error_msg_output(const char *input)
{
    int pipefd[2];
    char buffer[1024] = {0};
    int saved_stderr = dup(STDERR_FILENO);

    if (pipe(pipefd) == -1)
        return (1);
    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[1]);

    error_msg(input);

    fflush(stderr);
    ssize_t r = read(pipefd[0], buffer, sizeof(buffer) - 1);
    if (r <= 0) buffer[0] = '\0';
    close(pipefd[0]);
    dup2(saved_stderr, STDERR_FILENO);
    close(saved_stderr);

    if (strcmp(buffer, input) != 0)
    {
        fprintf(stderr, "❌ error_msg(\"%s\") wrote \"%s\" (expected exact match)\n", input, buffer);
        return (1);
    }
    return (0);
}

int test3(void)
{
    int fails = 0;

    fails += test_error_msg_output("Erreur critique\n");
    fails += test_error_msg_output("");
    fails += test_error_msg_output("Une erreur très longue avec plein de détails : valeur X invalide, paramètre Y manquant, etc.\n");

    if (fails == 0)
    {
        write(1, "✅ All error_msg output tests passed.\n", 38);
        return (0);
    }
    else
    {
        fprintf(stderr, "%d test(s) failed.\n", fails);
        return (1);
    }
}