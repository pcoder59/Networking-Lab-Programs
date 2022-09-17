#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main() {
    int i = 1, noframes, x;
    printf("Enter Number of Frams: ");
    scanf("%d", &noframes);
    while(noframes > 0) {
        printf("Sending Frame %d\n", i);
        srand(x++);
        x = rand()%10;
        if(x%2 == 0) {
            printf("Waiting for 1 Second...\n");
            sleep(1);
            printf("Missing Acknowledgement for frame %d\nResending frame %d\n", i, i);
        }
        printf("Acknowledgement Received for Frame %d\n", i);
        noframes--;
        i++;
    }
    printf("End of Stop and Wait Protocol!\n");
    return 0;
}