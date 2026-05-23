#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, faults = 0;

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
            int empty = -1;

            for(int j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if(empty != -1) {
                frames[empty] = pages[i];
            } else {
                int farthest = -1;
                int replace = -1;

                for(int j = 0; j < f; j++) {
                    int k;

                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == pages[k]) {
                            break;
                        }
                    }

                    if(k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }

                frames[replace] = pages[i];
            }

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

To minimize page faults by replacing the page that will not be used for the longest future time.

Theory

Optimal Page Replacement gives the minimum possible page faults.

Rule:

Replace page whose next use is farthest in future.

Working Example

Frames = 3

Reference:

1 2 3 4

Memory:

1 → 1
2 → 1 2
3 → 1 2 3
4 → remove page used farthest later

OS looks into future.

Algorithm (Optimal Page Replacement)
Start
Initialize frames
Read page reference
If page present → hit
Else page fault
If frame free → insert page
Else look ahead in reference string
Find page used farthest in future
Replace that page
Repeat until complete
Stop
*/