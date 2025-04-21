//USE IN ONLINE GDB

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define MAX_ITERATIONS 3

sem_t chopsticks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2 + 1); // Thinking

        sem_wait(&chopsticks[left]);
        sem_wait(&chopsticks[right]);
        printf("Philosopher %d picked up chopsticks %d and %d.\n", id, left, right);

        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2 + 1); // Eating

        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
        printf("Philosopher %d put down chopsticks %d and %d.\n", id, left, right);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    srand(time(NULL)); // Seed the random number generator

    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        sem_init(&chopsticks[i], 0, 1);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, (void*)&ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        pthread_join(threads[i], NULL);

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        sem_destroy(&chopsticks[i]);

    return 0;
}
