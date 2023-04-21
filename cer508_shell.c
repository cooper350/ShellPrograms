/* 
netID: cer508
name: Cooper Riley

Shell Program
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10 // Maximum number of command line arguments
#define MAX_LENGTH 100 // Maximum length of the command line input

int main() {
    char input[MAX_LENGTH]; // Buffer for command line input
    char *args[MAX_ARGS]; // Array to store command line arguments
    int i, status;
    pid_t pid;

    while(1) {
        printf(">> ");
        fgets(input, MAX_LENGTH, stdin); // Read input from user

        // Remove the newline character from input
        input[strcspn(input, "\n")] = 0;

        // Tokenize the input into arguments
        char *token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_ARGS-1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Set last argument to NULL for execvp()

        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir(getenv("HOME"));
            } else {
                chdir(args[1]);
            }
        } else {
            pid = fork();
            if (pid == 0) {
                // Child process
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            } else if (pid > 0) {
                // Parent process
                waitpid(pid, &status, 0);
            } else {
                perror("fork");
            }
        }
    }
    return 0;
}
