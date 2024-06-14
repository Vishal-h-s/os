#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    int firstAttempt = 1;

    // Try to open the named pipe for reading, retrying until it succeeds
    while ((fd = open(FIFO_NAME, O_RDONLY)) == -1) {
        if (firstAttempt) {
            printf("Reader: Waiting for the writer to create the FIFO...\n");
            firstAttempt = 0;
        }
        sleep(1);
    }

    // Read the message from the named pipe
    ssize_t numBytes = read(fd, buffer, BUFFER_SIZE);
    if (numBytes == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Null-terminate the read buffer to avoid garbage data at the end
    buffer[numBytes] = '\0';

    printf("Reader: Received message '%s'\n", buffer);

    close(fd);
    
    // Remove the FIFO after use
    if (unlink(FIFO_NAME) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    printf("Reader: Deleted the FIFO '%s'\n", FIFO_NAME);

    return 0;
}
