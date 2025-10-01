#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, completed;
};

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;

    // For storing Gantt chart sequence
    int order[n], finish[n], k = 0;

    printf("\nGantt Chart (SJF Non-Preemptive):\n ");

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        // Execute chosen process
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;

        avgTAT += p[idx].tat;
        avgWT += p[idx].wt;

        // Store order + completion for Gantt chart
        order[k] = p[idx].pid;
        finish[k] = p[idx].ct;
        k++;

        completed++;
    }

    // Print top bar
    for (i = 0; i < k; i++) {
        printf("-------");
    }
    printf("\n|");

    // Print process order
    for (i = 0; i < k; i++) {
        printf("  P%d  |", order[i]);
    }

    // Bottom bar
    printf("\n ");
    for (i = 0; i < k; i++) {
        printf("-------");
    }
    printf("\n");

    // Timeline
    printf("0");
    for (i = 0; i < k; i++) {
        printf("%7d", finish[i]);
    }
    printf("\n");

    // Process Table
    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT = %.2f\n", avgWT / n);

    return 0;
}
