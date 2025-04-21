#include <stdio.h> 
#include <stdlib.h> 
void findSeekSequence(int arr[], int head, int n) { 
    int seek_sequence[n]; 
    int seek_count = 0; 
    seek_sequence[0] = head; 
    seek_count += abs(arr[0] - head); 
 
    for (int i = 1; i < n; i++) { 
        seek_sequence[i] = arr[i]; 
        seek_count += abs(arr[i] - arr[i - 1]); 
    } 
    printf("Seek Sequence: "); 
    for (int i = 0; i < n; i++) { 
        printf("%d ", seek_sequence[i]); 
    } 
    printf("\n"); 
 
    printf("Total seek operations = %d\n", seek_count); 
} 
int main() { 
    int arr[] = { 98, 183, 41, 122, 14, 124, 65, 67 };  
    int head = 53;  
int n = sizeof(arr) / sizeof(arr[0]); 
findSeekSequence(arr, head, n); 
return 0; 
} 