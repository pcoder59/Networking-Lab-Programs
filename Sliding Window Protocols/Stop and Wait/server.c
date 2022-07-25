#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct packet {
    char data[1024];
}Packet;

typedef struct frame {
    int sq_no;
    int frame_kind;
    int ack;
    Packet packet;
}Frame;

int main() {
    int socket_udp, port, frame_id = 0, ack;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    Frame Frame_recv, Frame_send;
    char n[5];
    printf("Creating UDP Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, n, sizeof(n), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Received Number of Frames\n");
    while(frame_id < atoi(n)) {
        recvfrom(socket_udp, &Frame_recv, sizeof(Frame_recv), 0, (struct sockaddr *)&serveraddr, &len);
        printf("Acknowledge Incoming Frame! Enter -1 for Negative Ack: ");
        scanf("%d", &ack);
        if(Frame_recv.sq_no == frame_id && Frame_recv.frame_kind == 0 && Frame_recv.ack == 0 && ack != -1) {
            printf("Frame Received: %s\n", Frame_recv.packet.data);
            Frame_send.sq_no = frame_id + 1;
            Frame_send.frame_kind = 0;
            Frame_send.ack = 1;
            sendto(socket_udp, &Frame_send, sizeof(Frame_send), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
            frame_id++;
            printf("Ack Sent!\n");
        } else {
            printf("Frame not Received!\n");
            Frame_send.sq_no = frame_id + 1;
            Frame_send.frame_kind = 0;
            Frame_send.ack = 0;
            sendto(socket_udp, &Frame_send, sizeof(Frame_send), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
            printf("Negative Ack Sent!\n");
        }
    }
    close(socket_udp);
    return 0;
}