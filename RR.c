#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt;
};

struct Queue {
    int items[100];
    int front, rear;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(struct Queue *q) {
    return q->front == q->rear;
}

void enqueue(struct Queue *q, int value) {
    q->items[q->rear++] = value;
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) return -1;
    return q->items[q->front++];
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  // remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;

    int timeline[200]; 
    int gantt[200];
    int idx = 0;

    struct Queue q;
    initQueue(&q);

    // First arrivals
    int added[100] = {0}; 
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            enqueue(&q, i);
            added[i] = 1;
        }
    }

    timeline[idx] = 0;

    printf("\nGantt Chart (Round Robin):\n ");
    for (int i = 0; i < 40; i++) printf("-");
    printf("\n|");

    while (completed < n) {
        if (isEmpty(&q)) {
            time++;
            for (int i = 0; i < n; i++) {
                if (!added[i] && p[i].at <= time) {
                    enqueue(&q, i);
                    added[i] = 1;
                }
            }
            continue;
        }

        int i = dequeue(&q);

        printf(" P%d |", p[i].pid);

        int execTime = (p[i].rt > tq) ? tq : p[i].rt;
        time += execTime;
        p[i].rt -= execTime;

        // check new arrivals during execution
        for (int j = 0; j < n; j++) {
            if (!added[j] && p[j].at <= time) {
                enqueue(&q, j);
                added[j] = 1;
            }
        }

        if (p[i].rt > 0) {
            enqueue(&q, i); // not finished, put back
        } else {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            avgTAT += p[i].tat;
            avgWT += p[i].wt;
            completed++;
        }

        timeline[++idx] = time;
        gantt[idx-1] = p[i].pid;
    }

    printf("\n ");
    for (int i = 0; i < 40; i++) printf("-");
    printf("\n");

    // Print timeline
    for (int i = 0; i <= idx; i++) {
        printf("%-5d", timeline[i]);
    }
    printf("\n");

    // Process Table
    printf("\nProcess Table:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", avgTAT / n);
    printf("\nAverage WT = %.2f\n", avgWT / n);

    return 0;
}
