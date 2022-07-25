#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct frame {
    int data;
    int ack;
};

int main() {
    int n, i, r;
    printf("Enter Number of Packets: ");
    scanf("%d", &n);
    struct frame frm[n];
    for(i = 0; i < n; i++) {
        printf("Enter Data for Packet %d:", i+1);
        scanf("%d", &frm[i].data);
        frm[i].ack = 1;
    }
    r = rand()%n;
    frm[r].ack = -1;
    for(i = 0; i < n; i++) {
        if(frm[i].ack == -1) {
            printf("Packet %d not received!\n", r+1);
        }
    }
    printf("Resending Packet %d!\n", r+1);
    sleep(2);
    frm[r].ack = 1;
    printf("The received packet is %d\n", frm[r].data);
    return 0;
}