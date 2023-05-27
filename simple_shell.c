#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char command[BUFFER_SIZE];

    while (1) {
        printf("simple_shell$ ");
        if (fgets(command, sizeof(command), stdin) == NULL)
            break;  // EOF (Ctrl+D) reached, exit the shell

        command[strcspn(command, "\n")] = '\0';  // Remove trailing newline

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(command, command, NULL);  // Execute the command
            perror("execlp");  // Print an error if execution fails
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);  // Wait for the child process to complete
        }
    }

    return 0;
}
