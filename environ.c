 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *command) {
    pid_t pid = fork();
//main
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
    
        execlp(command, command, NULL);
        
        fprintf(stderr, "Command '%s' not found\n", command);
        exit(EXIT_FAILURE);
    } else {
        
        wait(NULL);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");  // Display prompt
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        execute_command(command);
    }

    return 0;
}
