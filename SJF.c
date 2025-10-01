#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, completed;
};

struct Queue {
    int items[200];
    int front, rear;
};

void initQueue(struct Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(struct Queue *q) {
    return q->front == q->rear;
}

void enqueue(struct Queue *q, int x) {
    q->items[q->rear++] = x;
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
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    float avgTAT = 0, avgWT = 0;

    // For Gantt Chart
    int order[200], finish[200], k = 0;

    struct Queue q;
    initQueue(&q);
    int added[100] = {0};

    // Initially add processes that arrived at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            enqueue(&q, i);
            added[i] = 1;
        }
    }

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

        int execTime = (p[i].rt > tq) ? tq : p[i].rt;
        time += execTime;
        p[i].rt -= execTime;

        order[k] = p[i].pid;
        finish[k] = time;
        k++;

        // Check arrivals during execution
        for (int j = 0; j < n; j++) {
            if (!added[j] && p[j].at <= time) {
                enqueue(&q, j);
                added[j] = 1;
            }
        }

        if (p[i].rt > 0) {
            enqueue(&q, i);
        } else if (!p[i].completed) {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            p[i].completed = 1;
            avgTAT += p[i].tat;
            avgWT += p[i].wt;
            completed++;
        }
    }

    // Gantt Chart
    printf("\nGantt Chart (Round Robin):\n ");
    for (int i = 0; i < k; i++) printf("-------");
    printf("\n|");
    for (int i = 0; i < k; i++) printf("  P%d  |", order[i]);
    printf("\n ");
    for (int i = 0; i < k; i++) printf("-------");
    printf("\n");

    printf("0");
    for (int i = 0; i < k; i++) printf("%7d", finish[i]);
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
