#include <stdio.h>
#include <stdbool.h>

int main() {
    int np, nb;
    
    // Input number of partitions
    printf("Enter the number of memory partitions: ");
    scanf("%d", &nb);
    int partitions[nb], partitionAllocated[nb];
    
    printf("Enter the sizes of memory partitions:\n");
    for (int i = 0; i < nb; i++) {
        scanf("%d", &partitions[i]);
        partitionAllocated[i] = 0; // 0 = not allocated, 1 = allocated
    }
    
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &np);
    int process[np];
    
    printf("Enter the memory required for each process:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &process[i]);
    }

    // Allocation logic using Best Fit
    for (int i = 0; i < np; i++) {
        int bestIdx = -1;
        for (int j = 0; j < nb; j++) {
            if (!partitionAllocated[j] && partitions[j] >= process[i]) {
                if (bestIdx == -1 || partitions[j] < partitions[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            printf("Process %d allocated to partition of size %d\n", i + 1, partitions[bestIdx]);
            partitionAllocated[bestIdx] = 1;
        } else {
            printf("Process %d cannot be allocated memory.\n", i + 1);
        }
    }

    return 0;
}
