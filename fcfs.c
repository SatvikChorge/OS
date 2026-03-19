#include<stdio.h>

int main() {
    int n, temp;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    
    for(int i = 0; i < n; i++){
        pid[i] = i + 1;
        printf("Enter ARRIVAL and BURST time for P%d : ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    for(int i = 0; i < n -1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(at[j] > at[j+1]){
                temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                temp = pid[j];
                pid[j] = pid[j+1];
                pid[j+1] = temp;
            }
        }
    }

    ct[0] = at[0] + bt[0];
    rt[0] = 0;   
    
    for(int i = 1; i < n; i++){
        if(ct[i-1] > at[i]){
            rt[i] = ct[i-1] - at[i];  
            ct[i] = ct[i-1] + bt[i];
        }
        else{
            rt[i] = 0;   
            ct[i] = at[i] + bt[i];
        }
    }

    for(int i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
    }

    for(int i = 0; i < n; i++){
        wt[i] = tat[i] - bt[i];
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
        pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    return 0;
}