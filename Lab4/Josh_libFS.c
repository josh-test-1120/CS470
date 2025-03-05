#include "Josh_libFS.h"
#include <dirent.h>

// Global variables
FileEntry file_table[MAX_FILES];  // File table to track files
int file_count = 0;               // Number of files in the system
size_t length = 0;                // size of data

// Initialize file array
int fileInit() {
    // Variables
    DIR *dir;
    struct dirent *entry;
    char *filenames[MAX_FILES];

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL && file_count < MAX_FILES) {
        // Allocate memory for each filename
        filenames[file_count] = malloc(MAX_FILENAME);
        if (filenames[file_count] == NULL) {
            perror("Unable to allocate memory");
            return 1;
        }
        // Calculate length of filename
        length = strlen(entry->d_name);

        // If the last characters (minus the EOF) are .txt
        if ((entry->d_name[length - 4] == '.') && 
            (entry->d_name[length - 3] == 't') && 
            (entry->d_name[length - 2] == 'x') && 
            (entry->d_name[length - 1] == 't')) {
            // Copy the filename into the array
            strcpy(file_table[file_count].filename, entry->d_name);
            file_count++;
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}

// Create a new file
int fileCreate(const char *filename) {

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}

// Open a file
int fileOpen(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            if (file_table[i].is_open) {
                printf("Error: File '%s' is already open.\n", filename);
                return -1;
            }
            file_table[i].is_open = 1;  // Mark file as open
            printf("File '%s' opened successfully.\n", filename);
            return i;  // Return file index
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}

// Write data to a file
int fileWrite(int file_index, const char *data) {
    // Check to make sure file is open
    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }
    // Get the length of the data to write
    length = strlen(data);

    // Write data to the local file
    FILE *file = fopen(file_table[file_index].filename, "w");
    if (!file) {
        printf("Error: Unable to open file '%s' for writing.\n", file_table[file_index].filename);
        return -1;
    }
    fwrite(data, 1, length, file);
    fclose(file);

    file_table[file_index].size = length;
    printf("Data written to file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}

// Read data from a file
int fileRead(int file_index, char *buffer, int buffer_size) {
    // Check to make sure file is open
    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    // Read data from the local file
    FILE *file = fopen(file_table[file_index].filename, "r");
    if (!file) {
        printf("Error: Unable to open file '%s' for reading.\n", file_table[file_index].filename);
        return -1;
    }
    length = fread(buffer, sizeof(buffer), buffer_size, file);
    fclose(file);
    printf("Length of bytes: %ld\n", length);
    printf("Length of buffer: %ld\n", strlen(buffer));
    printf("Last buffer index: %c\n", buffer[strlen(buffer)-1]);

    printf("Data read from file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}


// Close a file
int fileClose(int file_index) {
    char *filename = file_table[file_index].filename;
    // Check to make sure file is not already closed
    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is already closed.\n", filename);
        return -1;
    }
    else {
        file_table[file_index].is_open = 0;  // Mark file as closed
        printf("File '%s' closed successfully.\n", filename);
    }
    return 0;
}


// Delete a file
int fileDelete(const char *filename) {
    // Variables
    int found = 0;
    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) found = i;
    }

    if (found) {
        printf("Error: File '%s' does not exists.\n", filename);
        return -1;
    }
    
    // Delete the file
    if (remove(filename) == 0) printf("File '%s' deleted successfully.\n", filename);
    else {
        perror("Error deleting file");
        return 1;
    }

    // Iterate from file to end of files and shift left
    for (int i = found; i < file_count-1; i++) {
        file_table[i] = file_table[i+1];
    }

    // Update the file count
    file_count--;

    return 0;
}