#include <stdio.h> 
#include <stdbool.h>
void main() { 
    int n, m, max; 
    bool first = false; 
    printf("Enter the number of partitions: "); 
    scanf("%d", &n); 
    int arr[n];  
    printf("\nEnter the elements: "); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &arr[i]); 
    }  
    printf("Enter the memory required for process: "); 
    scanf("%d", &m); 
    for (int i = 0; i < n; i++) { 
        if (arr[i] >= m) { 
            if (!first || arr[i] > max) { 
                max = arr[i]; 
                first = true; 
            } 
        } 
    } 
    if (first) { 
        printf("Memory allocated is %d\n", max); 
    } else { 
        printf("No suitable memory block available.\n"); 
    } 
}