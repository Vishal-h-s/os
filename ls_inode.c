#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


// Function to list files in a directory along with their inode numbers
void listFiles(const char *path) {
    struct dirent *entry; // Directory entry structure
    struct stat fileStat; // File status structure
    char fullPath[1024];  // Buffer to hold full path of file
    DIR *dp = opendir(path); // Open directory

    if (dp == NULL) { // Check if directory opened successfully
        perror("opendir");
        return;
    }

    printf("Listing files in directory: %s\n", path);
    while ((entry = readdir(dp)) != NULL) { // Read each directory entry
        // Construct full path of the file
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);
        // Get file status
        if (stat(fullPath, &fileStat) < 0) {
            perror("stat");
            continue;
        }
        // Print inode number and file name
        printf("Inode: %lu, Name: %s\n", (unsigned long)entry->d_ino, entry->d_name);
    }
    closedir(dp); // Close directory
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // Check if directory path is provided
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    listFiles(argv[1]); // List files in the provided directory

    return 0;
}
