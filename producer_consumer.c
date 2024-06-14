#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1
#define SEM_PRODUCER "/sem_producer"
#define SEM_CONSUMER "/sem_consumer"

// Shared buffer and semaphores
int buffer;
sem_t *semProducer, *semConsumer;

// Producer function
void producer()
{
    int item = 0;

    while (1)
    {
        // Produce item
        item++;

        // Wait until buffer is empty
        sem_wait(semProducer);

        // Produce item and place in buffer
        buffer = item;
        printf("Producer produced item: %d\n", item);

        // Signal that item is available
        sem_post(semConsumer);

        sleep(rand() % 3); // Simulate production time
    }
}

// Consumer function
void consumer()
{
    int item;

    while (1)
    {
        // Wait until item is available
        sem_wait(semConsumer);

        // Consume item from buffer
        item = buffer;
        printf("Consumer consumed item: %d\n", item);

        // Signal that buffer is empty
        sem_post(semProducer);

        sleep(rand() % 3); // Simulate consumption time
    }
}

int main()
{
    // Initialize semaphores
    semProducer = sem_open(SEM_PRODUCER, O_CREAT, 0644, BUFFER_SIZE);
    semConsumer = sem_open(SEM_CONSUMER, O_CREAT, 0644, 0);

    if (semProducer == SEM_FAILED || semConsumer == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid;

    // Create a child process for producer
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        producer();
        exit(0);
    }

    // Create another child process for consumer
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        consumer();
        exit(0);
    }

    // Wait for both child processes to complete
    wait(NULL);
    wait(NULL);

    // Close and unlink semaphores
    sem_close(semProducer);
    sem_close(semConsumer);
    sem_unlink(SEM_PRODUCER);
    sem_unlink(SEM_CONSUMER);

    return 0;
}
