#include <stdio.h> 
 
void main() { 
    int n, m,allot=-1; 
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
            allot=arr[i]; 
            break; 
        } 
    }
    if (allot!=-1) { 
        printf("Memory allocated is %d\n", allot); 
    } else { 
        printf("No suitable memory block available.\n"); 
    } 
} 