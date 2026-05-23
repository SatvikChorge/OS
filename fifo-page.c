#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, index = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(int i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(found == 0) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        printf("%d\t", pages[i]);

        for(int j = 0; j < f; j++) {
            if(frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
/*
Aim

To replace pages in memory using arrival order.

Theory

FIFO is the simplest page replacement algorithm.

Rule:

Page that entered memory first is removed first.

Uses queue structure.

Working Example

Frames = 3

Reference String:

1 2 3 4

Memory:

1 → 1
2 → 1 2
3 → 1 2 3
4 → remove 1

Result:

4 2 3

because page 1 was oldest.

Algorithm (FIFO)
Start
Initialize empty frame queue
Read page reference
If page already present → hit
Else page fault
If free frame available → insert
Else remove oldest page
Insert new page
Repeat until references end
Stop

*/