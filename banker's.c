#include <stdio.h>

int main() {
    int n, m;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10] = {0}, safe[10];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Max Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int canRun = 1;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if(canRun == 1) {
                    for(int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is not in safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in safe state.");
    printf("\nSafe Sequence: ");

    for(int i = 0; i < n; i++) {
        printf("P%d ", safe[i]);
    }

    return 0;
}

/*
Aim

To avoid deadlock by allocating resources only if the system remains in a safe state.

Theory

Banker’s Algorithm is a deadlock avoidance technique.

The OS acts like a banker:

Loans resources carefully
Grants request only if system remains safe
Avoids deadlock before it occurs
Important Terms
1. Available

Resources currently free.

2. Max

Maximum resources a process may need.

3. Allocation

Resources already assigned.

4. Need

Remaining resources needed.

Need = Max − Allocation

Safe State

System can complete all processes without deadlock.

Unsafe State

Deadlock may occur.

Example

Suppose:

Total printers = 5
Some already allocated
New request arrives

OS checks:

“If I allocate now, can all processes still finish?”

If yes → grant
If no → deny.

Algorithm (Banker’s Algorithm)
Safety Algorithm
Start
Calculate Need = Max − Allocation
Find process whose Need ≤ Available
If found → allocate temporarily
Process finishes and releases resources
Add released resources to Available
Repeat for remaining processes
If all finish → Safe state
Else → Unsafe state
Stop
Resource Request Algorithm
Process requests resources
Check Request ≤ Need
Check Request ≤ Available
Allocate temporarily
Run Safety Algorithm
If safe → grant request
Else rollback allocation
Stop
*/