#include <stdio.h>

int main() {
    int n, bt[20], pr[20], p[20], wt[20], tat[20], temp;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter burst time and priority for P%d: ", i + 1);
        scanf("%d %d", &bt[i], &pr[i]);
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(pr[i] > pr[j]) {
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    wt[0] = 0;

    for(int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    printf("\nProcess\tBT\tPriority\tWT\tTAT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t%d\t\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
