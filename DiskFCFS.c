#include <stdio.h>
#include <stdlib.h>

void findSeekSequence(int arr[], int head, int n) {
    int seek_sequence[n + 1]; // Increased size to accommodate the initial head
    int seek_count = 0;

    // The first position in the seek sequence is the initial head position
    seek_sequence[0] = head;

    // Calculate the seek distance for the first request from the head
    seek_count = abs(arr[0] - head);
    seek_sequence[1] = arr[0];

    // Calculate the seek distance for each subsequent request
    for (int i = 1; i < n; i++) {
        seek_sequence[i + 1] = arr[i];
        seek_count += abs(arr[i] - arr[i - 1]); // Adding the distance between consecutive requests
    }

    printf("Seek Sequence: ");
    for (int i = 0; i <= n; i++) { // Loop up to and including n to print all elements
        printf("%d ", seek_sequence[i]);
    }
    printf("\n");

    printf("Total seek operations = %d\n", seek_count);
}

int main() {
    int arr[] = {98, 183, 41, 122, 14, 124, 65, 67}; // Disk requests
    int head = 53;  // Initial head position
    int n = sizeof(arr) / sizeof(arr[0]); // Number of requests

    findSeekSequence(arr, head, n);

    return 0;
}
