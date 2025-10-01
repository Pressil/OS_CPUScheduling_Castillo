#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
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
    }

    int time = 0;
    float avgTAT = 0, avgWT = 0;

    printf("\nGantt Chart (FCFS):\n ");

    // Top bar
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");

    // Process order
    for (i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
        printf("  P%d  |", p[i].pid);
    }

    // Bottom bar
    printf("\n ");
    for (i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n");

    // Timeline
    time = 0;
    printf("0");
    for (i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        printf("%7d", time);
    }
    printf("\n");

    // Table
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
