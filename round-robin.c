#include <stdio.h>

int main() {
    int n, bt[20], rem[20], wt[20] = {0}, tat[20], tq;
    int time = 0, done;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    do {
        done = 1;

        for(int i = 0; i < n; i++) {
            if(rem[i] > 0) {
                done = 0;

                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    wt[i] = time - bt[i];
                    rem[i] = 0;
                }
            }
        }
    } while(!done);

    printf("\nProcess\tBT\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}

/*
Aim

To provide fair CPU sharing among processes using time slices.

Theory

Round Robin is mainly used in time-sharing systems.

Each process gets CPU for a fixed Time Quantum (TQ).
If process finishes → removed.
If not → moved to end of queue.

Works like circular queue rotation.

Working Example

Time Quantum = 2 ms

| Process | Burst |
| ------- | ----: |
| P1      |     5 |
| P2      |     4 |
| P3      |     3 |
Execution:

P1 → P2 → P3 → P1 → P2 → P3 → P1

until completion.

Algorithm (Round Robin)
Start
Place processes in ready queue
Choose first process
Allocate CPU for fixed time quantum
If process finishes → remove
Else move it to rear of queue
Select next process
Repeat until all complete
Stop
*/