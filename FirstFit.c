#include <stdio.h>

int main() {
    int nb, np;

    // Input number of partitions
    printf("Enter the number of memory partitions: ");
    scanf("%d", &nb);
    int partitions[nb], partitionAllocated[nb];

    printf("Enter the sizes of memory partitions:\n");
    for (int i = 0; i < nb; i++) {
        scanf("%d", &partitions[i]);
        partitionAllocated[i] = 0; // 0 = not allocated
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &np);
    int processes[np];

    printf("Enter the memory required for each process:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &processes[i]);
    }

    // First Fit Allocation
    for (int i = 0; i < np; i++) {
        int allotted = -1;
        for (int j = 0; j < nb; j++) {
            if (!partitionAllocated[j] && partitions[j] >= processes[i]) {
                allotted = j;
                partitionAllocated[j] = 1;
                break;
            }
        }

        if (allotted != -1) {
            printf("Process %d allocated to partition of size %d\n", i + 1, partitions[allotted]);
        } else {
            printf("Process %d cannot be allocated memory.\n", i + 1);
        }
    }

    return 0;
}
