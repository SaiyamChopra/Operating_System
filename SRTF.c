#include <stdio.h>
#define MAX 20

int main() {
    int bt[MAX], at[MAX], rt[MAX], ct[MAX]; // ct = completion time
    int i, smallest, count = 0, time, n, end;
    int wait_time = 0, turnaround_time = 0;
    float avg_wait_time, avg_turnaround_time;

    int exec_seq[MAX * 100]; // Store execution sequence
    int seq_index = 0;

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

    rt[19] = 9999; // Sentinel

    for (time = 0; count != n; time++) {
        smallest = 19;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }

        exec_seq[seq_index++] = smallest + 1; // Log execution

        rt[smallest]--;

        if (rt[smallest] == 0) {
            count++;
            end = time + 1;
            ct[smallest] = end;
        }
    }

    printf("\nExecution Timeline:\n0 ");
    for (i = 1; i < seq_index; i++) {
        if (exec_seq[i] != exec_seq[i - 1]) {
            printf("-> P%d -> %d ", exec_seq[i - 1], i);
        }
    }
    printf("-> P%d -> %d\n", exec_seq[seq_index - 1], seq_index);

    // Calculate and show results
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        int tat = ct[i] - at[i];
        int wt = tat - bt[i];
        turnaround_time += tat;
        wait_time += wt;
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat, wt);
    }

    avg_wait_time = (float)wait_time / n;
    avg_turnaround_time = (float)turnaround_time / n;

    printf("\nAverage Waiting Time = %.2f", avg_wait_time);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turnaround_time);

    return 0;
}
