#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, total_movement = 0, current_position;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &current_position);

    printf("\nFCFS Disk Scheduling\n");
    printf("Request Order: %d", current_position);

    for (i = 0; i < n; i++) {
        total_movement += abs(requests[i] - current_position);
        current_position = requests[i];
        printf(" -> %d", requests[i]);
    }

    printf("\n\nTotal Head Movement = %d cylinders\n", total_movement);

    return 0;
}
