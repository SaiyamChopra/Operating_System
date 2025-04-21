/*Enter number of processes: 3
Enter arrival time and burst time for each process:
P1 arrival time: 0
P1 burst time: 7
P2 arrival time: 2
P2 burst time: 4
P3 arrival time: 4
P3 burst time: 1

Process	Arrival	Burst	Completion	Turnaround	Waiting
P3	    4	    1	    5		    1		    0
P2	    2	    4	    9		    7		    3
P1	    0	    7	    16		    16		    9

Average Waiting Time = 4.00  
Average Turnaround Time = 8.00
*/
#include <stdio.h>
#define MAX 20

int main() {
    int bt[MAX], at[MAX], rt[MAX]; // Burst, Arrival, Remaining times
    int i, smallest, count = 0, time, n;
    int wait_time = 0, turnaround_time = 0, end;
    float avg_wait_time, avg_turnaround_time;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d arrival time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d burst time: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    rt[19] = 9999; // Sentinel value

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    for (time = 0; count != n; time++) {
        smallest = 19;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }

        rt[smallest]--;

        if (rt[smallest] == 0) {
            count++;
            end = time + 1;
            int tat = end - at[smallest];     // Turnaround time
            int wt = tat - bt[smallest];      // Waiting time
            wait_time += wt;
            turnaround_time += tat;

            printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", smallest + 1, at[smallest], bt[smallest], end, tat, wt);
        }
    }

    avg_wait_time = (float)wait_time / n;
    avg_turnaround_time = (float)turnaround_time / n;

    printf("\nAverage Waiting Time = %.2f", avg_wait_time);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turnaround_time);

    return 0;
}
