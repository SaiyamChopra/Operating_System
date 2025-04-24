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












#include <stdio.h>

#define N 5  // Number of philosophers and chopsticks

int chopstick[N] = {0};  // 0 = free, 1 = taken

// Function to simulate wait
int wait(int i) {
    if (chopstick[i] == 0) {
        chopstick[i] = 1;  // Take chopstick
        return 1;          // Success
    }
    return 0;              // Failed to take chopstick
}

// Function to simulate signal
void signal(int i) {
    chopstick[i] = 0;  // Release chopstick
}

int main() {
    for (int i = 0; i < N; i++) {
        printf("Philosopher %d is trying to eat...\n", i);

        // Try to pick up both left and right chopsticks
        if (wait(i) && wait((i + 1) % N)) {
            printf("Philosopher %d is eating using chopsticks %d and %d.\n", i, i, (i + 1) % N);

            // After eating, put down both chopsticks
            signal(i);
            signal((i + 1) % N);

            printf("Philosopher %d finished eating and is now thinking.\n", i);
        } else {
            // Couldn't eat because one of the chopsticks is busy
            printf("Philosopher %d couldn't eat (one or both chopsticks busy).\n", i);

            // If one chopstick was picked, release it
            if (chopstick[i] == 1) signal(i);
            if (chopstick[(i + 1) % N] == 1) signal((i + 1) % N);
        }

        printf("\n");
    }

    return 0;
}
