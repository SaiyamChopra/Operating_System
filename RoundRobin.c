/*Enter the number of processes: 3
Enter Arrival Time and Burst Time for P1: 0 5
Enter Arrival Time and Burst Time for P2: 1 3
Enter Arrival Time and Burst Time for P3: 2 1
Enter Time Quantum: 2

Process	Turnaround Time	Waiting Time
P3	    3		        2
P2	    7		        4
P1	    9		        4

Average Waiting Time: 3.33
Average Turnaround Time: 6.33
*/
#include <stdio.h>
#define MAX 100

int main() {
    int bt[MAX], rt[MAX], at[MAX], wt[MAX], tat[MAX];
    int i, n, time = 0, remain, tq;
    float avg_wt = 0, avg_tat = 0;
    int sequence[MAX * 10]; // Stores execution order
    int seq_index = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nExecution Sequence:\n");

    int done[MAX] = {0};

    while (remain != 0) {
        int executed = 0;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                executed = 1;

                // Record process execution
                sequence[seq_index++] = i + 1;
                if (rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    avg_wt += wt[i];
                    avg_tat += tat[i];
                    remain--;
                    done[i] = 1;
                } else {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }

        if (!executed)
            time++;
    }

    // Print execution order
    for (i = 0; i < seq_index; i++) {
        if (i != 0) printf(" -> ");
        printf("P%d", sequence[i]);
    }

    printf("\n\nProcess\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", i + 1, tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
