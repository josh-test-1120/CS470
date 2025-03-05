#include "Josh_libFS.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    //getchar();  // Clear the newline character from the buffer
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Joshua Summers.\n\n"
                          "I am a computer science student passionate about computer sciences.\n"
                          "This project involves functions in a basic file system library in C.\n\n"
                          "I enjoy computer graphics and game engine development.\n"
                          "I hope you find this illuminating!";
    
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    // Initialize the file array
    fileInit();

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Reading introduction from file '%s'...\n", filename);
                    if (fileRead(file_index, buffer, MAX_FILE_SIZE) != 0) {
                        printf("Error reading from file.\n");
                    }
                }

                // Output the buffer
                printf("\n%s\n", buffer);

                waitForUser();
                break;
            
            case 5:  // Close the file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Closing file '%s'...\n", filename);
                    if (fileClose(file_index) != 0) {
                        printf("Error closing file.\n");
                    } else file_index = -1;
                }
                waitForUser();
                break;
            
            case 6:  // Delete the file
                if (file_index != -1) {
                    printf("Error: File is open. Please close the file first.\n");
                } else {
                    printf("Enter the filename to delete: ");
                    fgets(filename, MAX_FILENAME, stdin);
                    filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                    printf("Deleting file %s...\n", filename);
                    if (fileDelete(filename) != 0) {
                        printf("Error deleting file.\n");
                    }
                }
                waitForUser();
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}