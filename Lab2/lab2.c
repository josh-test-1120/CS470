// Author: Joshua Summers
// Lab2

// Included libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Main program
int main(int argc, char* argv[]) {
    // Variables
    pid_t pid;
    int status;
    char errString[150];
    const int numChildren = 10;

    // Array of commandds
    char* commands[][10] = {
        {"ls", "-la", NULL}, // Directory listing command
        {"echo", "Hello from Joshua Summers", NULL}, // echo output command
        {"date", NULL, NULL}, // date output command
        {"mkdir", "-p", "test_directory", NULL}, // create test directory command
        {"touch", "./test_directory/test_file1.txt", NULL}, // create test file command
        {"touch", "./test_directory/test_file2.txt", NULL}, // create test file command
        {"ps", "-a", NULL}, // ps output
        {"head", "lab2.c", "-n", "10", NULL}, // less output limited by more
        // Find command for file searching
        {"ls", "-l", NULL}, // Different directory listing
        // Output of processes (limited to top 8 from head
        {"ls", "-la", "./test_directory/", NULL}, // test directory output
        // yeah, the output should be ugly
        {"echo", "Ok enough output overlapping", NULL}, 
    };

    // Parent instantiation
    printf("Parent PID: %d\n", getpid());
    // Start child threads
    printf("Child process history: -------\n");

    // Iterate through the children
    for (int x = 0; x < numChildren; x++) {
        // Create a new child process
        pid = fork();
        // Handle error case
        if (pid < 0) {
            perror("Fork Failed\n");
            exit(EXIT_FAILURE);
        // Normal child creation
        } else if (pid == 0) {
            printf("Child PID: %d - Executing commands: %s\n",
                getpid(), commands[x][0]);
            // Execute the commands
            execvp(commands[x][0], commands[x]);
            // Handle errors
            sprintf(errString, "Execution of commands on child PID: %d failed\n"
            , getpid());
            perror(errString);
            exit(EXIT_FAILURE);
        }
        // Parent process
        else { }
    }

    // While there are child processes wait
    while ((pid = wait(&status)) > 0) {
        printf("Child process with PID: %d finished\n", pid);
    }
    
    // Now parent process can continue and complete
    printf("Parent PID: %d finished\n",getpid());
    return EXIT_SUCCESS;
}