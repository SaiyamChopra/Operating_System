/*Enter the number of processes: 4
Enter burst time for P1: 6
Enter burst time for P2: 8
Enter burst time for P3: 7
Enter burst time for P4: 3

Process	Burst Time	Waiting Time	Turnaround Time
P4	    3		    0		        3
P1	    6		    3		        9
P3	    7		    9		        16
P2	    8		    16		        24

Average Waiting Time = 7.00  
Average Turnaround Time = 13.00
*/
#include <stdio.h>

int main() {
    int n, i, j;
    int bt[20], p[20], wt[20], tat[20], temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst times and process numbers
    for (i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Process IDs
    }

    // Sort processes based on burst time (Simple Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process numbers
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0; // First process has 0 waiting time

    // Calculate waiting time for each process
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
