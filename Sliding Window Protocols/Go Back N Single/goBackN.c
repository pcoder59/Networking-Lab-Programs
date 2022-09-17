#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int n,r;

struct frame {
    int data;
    char ack;
}frm[10];

void sender() {
    int i;
    printf("Enter Number of Packets: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        printf("Enter Data For Packet[%d]: ", i+1);
        scanf("%d", &frm[i].data);
        frm[i].ack = 'y';
    }
}

void recvack() {
    int i;
    r = rand()%n;
    frm[r].ack = 'n';
    for(i = 0; i < n; i++) {
        if(frm[i].ack == 'n') {
            printf("Packet number %d is not Received!\n", i+1);
        }
    }
}

void rsend() {
    int i;
    printf("Resending From Packet %d\n", r+1);
    for(i = r; i < n; i++) {
        sleep(2);
        frm[i].ack = 'y';
        printf("Received data of packet %d is %d\n", i+1, frm[i].data);
    }
}

int main() {
    sender();
    recvack();
    rsend();
    return 0;
}