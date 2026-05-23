#include <stdio.h>

int main() {
    int n, at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int completed[20] = {0}, p[20];
    int time = 0, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    while(count < n) {
        int idx = -1;
        int minBT = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(bt[i] < minBT) {
                    minBT = bt[i];
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
        } else {
            time += bt[idx];
            ct[idx] = time;

            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            rt[idx] = wt[idx];

            completed[idx] = 1;
            count++;
        }
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    return 0;
}

/*
Aim

To minimize average waiting time by executing the shortest process first.

Theory

SJF selects the process with the smallest burst time.

Types:

1. Non-preemptive SJF
Once CPU is assigned, process finishes completely.
2. Preemptive SJF (Shortest Remaining Time First – SRTF)
If a shorter process arrives, CPU switches to it.
Working Example
| Process | Burst Time |
| ------- | ---------: |
| P1      |          8 |
| P2      |          4 |
| P3      |          2 |
Execution:

P3 → P2 → P1

because shortest burst executes first.

Algorithm (SJF)
Start
Put processes in ready queue
Select process with shortest burst time
Allocate CPU
Execute process
Remove completed process
Repeat until queue empty
Stop
*/