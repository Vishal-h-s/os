#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

// Function to handle errors
void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();
    if (pid < 0) {
        handle_error("fork");
    } else if (pid == 0) { // Child process
        while (1) {
            printf("Child: Running...\n");
            sleep(1);
        }
    } else { // Parent process
        sleep(3);  // Allow child to run for a few seconds

        // Send SIGSTOP to suspend the child process
        if (kill(pid, SIGSTOP) == -1) {
            handle_error("kill SIGSTOP");
        }
        printf("Parent: Sent SIGSTOP to child, child is suspended.\n");

        sleep(5);  // Wait for a few seconds while the child is suspended

        // Send SIGCONT to resume the child process
        if (kill(pid, SIGCONT) == -1) {
            handle_error("kill SIGCONT");
        }
        printf("Parent: Sent SIGCONT to child, child is resumed.\n");

        sleep(3);  // Allow child to run for a few more seconds

        // Send SIGTERM to terminate the child process
        if (kill(pid, SIGTERM) == -1) {
            handle_error("kill SIGTERM");
        }
        printf("Parent: Sent SIGTERM to child, waiting for child to terminate.\n");

        // Wait for the child process to terminate
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            handle_error("waitpid");
        }

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: Child was killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Parent: Child ended unexpectedly\n");
        }
    }

    return 0;
}
