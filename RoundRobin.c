#include <stdio.h>
#include <string.h>

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst[n], remaining[n], waiting[n], turnaround[n], completion[n];
    char processes[n][10];
    for (int i = 0; i < n; i++) {
        printf("Enter process name: ");
        scanf("%s", processes[i]);
        printf("Enter burst time for %s: ", processes[i]);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
        waiting[i] = 0;
        turnaround[i] = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    int time = 0, completed = 0;
    char ganttProcesses[100][10];
    int ganttTimes[100];
    int ganttIndex = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                ganttTimes[ganttIndex] = time;
                strcpy(ganttProcesses[ganttIndex], processes[i]);
                ganttIndex++;

                if (remaining[i] <= quantum) {
                    time += remaining[i];
                    remaining[i] = 0;
                    completed++;
                    completion[i] = time;
                } else {
                    time += quantum;
                    remaining[i] -= quantum;
                }
            }
        }
    }

    ganttTimes[ganttIndex] = time;

    float totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i];
        waiting[i] = turnaround[i] - burst[i];
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];
    }

    float avgWaiting = totalWaiting / n;
    float avgTurnaround = totalTurnaround / n;

    printf("\n");
    printf("| %-16s | %-10s | %-14s | %-14s |\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-16s | %-10d | %-14d | %-14d |\n", processes[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTurnaround);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++) {
        printf("| %-3s ", ganttProcesses[i]);
    }
    printf("|\n");

    for (int i = 0; i <= ganttIndex; i++) {
        printf("%-5d", ganttTimes[i]);
    }

    printf("\n");
    return 0;
}
