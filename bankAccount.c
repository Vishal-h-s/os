#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

#define SEM_NAME "/account_semaphore"
#define INITIAL_BALANCE 1000

// Shared account balance
int account_balance = INITIAL_BALANCE;

// Semaphore
sem_t *account_sem;

// Function to deposit an amount
void deposit(int amount) {
    sem_wait(account_sem);

    account_balance += amount;
    printf("Deposited %d, new balance: %d\n", amount, account_balance);

    sem_post(account_sem);
}

// Function to withdraw an amount
void withdraw(int amount) {
    sem_wait(account_sem);

    if (account_balance >= amount) {
        account_balance -= amount;
        printf("Withdrew %d, new balance: %d\n", amount, account_balance);
    } else {
        printf("Insufficient funds for withdrawal of %d, current balance: %d\n", amount, account_balance);
    }

    sem_post(account_sem);
}

int main() {
    pid_t pid;

    // Initialize semaphore
    account_sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (account_sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Perform deposit
        deposit(500);
        exit(0);
    } else { // Parent process
        // Wait for child to complete
        wait(NULL);

        // Attempt to withdraw
        withdraw(700);
        withdraw(500);

        // Close and unlink semaphore
        sem_close(account_sem);
        sem_unlink(SEM_NAME);

        return 0;
    }
}
