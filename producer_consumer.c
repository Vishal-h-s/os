#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 1
#define SEM_PRODUCER "/sem_producer"
#define SEM_CONSUMER "/sem_consumer"

// Shared buffer and semaphores
int *buffer;
sem_t *semProducer, *semConsumer;

void cleanup_resources() {
    sem_close(semProducer);
    sem_unlink(SEM_PRODUCER);
    sem_close(semConsumer);
    sem_unlink(SEM_CONSUMER);
    munmap(buffer, sizeof(int));
}

void producer() {
    int item = 0;
    while (1) {
        item++;
        sem_wait(semProducer);
        *buffer = item;
        printf("Producer produced item: %d\n", item);
        sem_post(semConsumer);
        sleep(rand() % 3);
    }
}

void consumer() {
    int item;
    while (1) {
        sem_wait(semConsumer);
        item = *buffer;
        printf("Consumer consumed item: %d\n", item);
        sem_post(semProducer);
        sleep(rand() % 3);
    }
}

int main() {
    srand(time(NULL)); // Initialize random seed

    // Create shared memory for the buffer
    buffer = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (buffer == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    semProducer = sem_open(SEM_PRODUCER, O_CREAT, 0644, 1);
    semConsumer = sem_open(SEM_CONSUMER, O_CREAT, 0644, 0);
    if (semProducer == SEM_FAILED || semConsumer == SEM_FAILED) {
        perror("sem_open");
        cleanup_resources();
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        cleanup_resources();
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        producer();
        exit(0);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        cleanup_resources();
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        consumer();
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    cleanup_resources();
    return 0;
}
