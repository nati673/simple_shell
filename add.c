#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int interactive()
{
    return (isatty(STDIN_FILENO));
}

int is_delim(char c, char *delim)
{
    while (*delim) {
        if (*delim++ == c)
            return 1;
    }
    return 0;
}

int _isalpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int _atoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return output;
}

void display_prompt()
{
    printf("$ ");
    fflush(stdout);
}

void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid ==
