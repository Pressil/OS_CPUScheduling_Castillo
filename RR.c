#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt; 
};

int main() {
    int n, tq, i, completed = 0, time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    float avgTAT = 0, avgWT = 0;

    printf("\nGantt Chart (Round Robin):\n ");

    for (i = 0; i < 40; i++) printf("-"); 
    printf("\n|");

    int timeline[200]; // stores the times for labels
    int timeline_idx = 0;
    timeline[timeline_idx++] = 0;

    while (completed < n) {
        int doneSomething = 0;
        for (i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                doneSomething = 1;

                printf(" P%d |", p[i].pid);

                if (p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    avgTAT += p[i].tat;
                    avgWT += p[i].wt;
                    completed++;
                }
                timeline[timeline_idx++] = time; // only update after a bar
            }
        }

        if (!doneSomething) {
            time++; 
        }
    }

    printf("\n ");
    for (i = 0; i < 40; i++) printf("-");
    printf("\n");

    // Print timeline aligned
    for (i = 0; i < timeline_idx; i++) {
        printf("%-5d", timeline[i]);
    }
    printf("\n");

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
