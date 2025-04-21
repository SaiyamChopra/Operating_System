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
    int flag = 0;
    float avg_wt = 0, avg_tat = 0;

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

    printf("\nProcess\tTurnaround Time\tWaiting Time\n");

    int complete[MAX] = {0}; // Flag to track completed processes

    while (remain != 0) {
        flag = 1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                flag = 0;
                if (rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    complete[i] = 1;
                } else {
                    rt[i] -= tq;
                    time += tq;
                }

                if (complete[i] && tat[i] == 0) {
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    avg_wt += wt[i];
                    avg_tat += tat[i];
                    printf("P%d\t%d\t\t%d\n", i + 1, tat[i], wt[i]);
                    remain--;
                }
            }
        }

        if (flag) time++; // If no process was ready, advance time
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
