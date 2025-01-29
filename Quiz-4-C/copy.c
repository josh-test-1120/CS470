// Author: Joshua Summers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// Constants
#define SOURCE_DIRECTORY "source-directory"
#define DESTINATION_DIRECTORY "destination-directory"

// Main program
int main(int argc, char* argv[]) {
    // Variables
    char intStr[11];
    char stringLabel[] = "";
    char src[50];
    char dst[50];
    char *ptr = stringLabel;

    // Program start
    printf("Creating the files and directories...\n");

    // Create the source and destination directories
    sprintf(ptr, "%s %s", "mkdir -p", SOURCE_DIRECTORY);
    sprintf(ptr + strlen(ptr), " %s", DESTINATION_DIRECTORY);
    // Run the command
    system(ptr);

    // Iteration for creating 100 files in the source directory
    for (int x=0; x < 100; x++) {
        // Convert the integer to a string
        sprintf(intStr, "%d", x);
        // Create the file in the directory
        sprintf(ptr, "%s %s", "touch", SOURCE_DIRECTORY);
        sprintf(ptr + strlen(ptr), "/%s", "file");
        sprintf(ptr + strlen(ptr), "%d", x);
        // Run the command
        system(ptr);
    }
    // Time to copy the files
    printf("Copying the files to destination directory...\n");
    // Create the proper formatted strings
    sprintf(src, "%s%s", SOURCE_DIRECTORY, "/");
    sprintf(dst, "%s%s", DESTINATION_DIRECTORY, "/");
    // Arguments
    char *cpargs[] = {"cp", "-r", src, dst, NULL};
    // Execute the cpargs
    execvp("cp", cpargs);
    // Handle any errors
    perror("Execution of cp failed");
    // Exit if failure
    exit(EXIT_FAILURE);
    // Program completed
    printf("Copy process complete.\n");
    // Return code is 0
    return 0;
}