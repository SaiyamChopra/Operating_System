#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5 // Buffer size

int buffer[SIZE];
int in = 0, out = 0;

// Semaphores and mutex
sem_t empty;     // Counts empty slots
sem_t full;      // Counts full slots
pthread_mutex_t mutex; // Ensures mutual exclusion

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item

        sem_wait(&empty); // Wait for empty slot
        pthread_mutex_lock(&mutex); // Lock buffer

        // Critical section
        buffer[in] = item;
        printf("Producer produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&full); // Signal that buffer has new item

        sleep(rand() % 2 + 1); // Simulate time taken to produce
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // Wait for item in buffer
        pthread_mutex_lock(&mutex); // Lock buffer

        // Critical section
        item = buffer[out];
        printf("Consumer consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer
        sem_post(&empty); // Signal that a slot is now empty

        sleep(rand() % 2 + 1); // Simulate time taken to consume
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads (infinite in this case)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean-up (won't be reached in this infinite loop version)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}















#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 3, x = 0;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("Producer produces the item %d\n", x);
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("Consumer consumes item %d\n", x);
    x--;
    mutex = signal(mutex);
}

int main() {
    int n;
    printf("\n1.Producer  2.Consumer  3.Exit");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);
        switch (n) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is full!!\n");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty!!\n");
                break;
            case 3:
                exit(1);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
