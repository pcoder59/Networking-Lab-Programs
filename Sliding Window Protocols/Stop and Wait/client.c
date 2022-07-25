#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct pack {
    char data[1024];
}Packet;

typedef struct frame {
    int sq_no;
    int frame_kind;
    int ack;
    Packet packet;
}Frame;

int main() {
    int socket_udp, port, frame_id = 0, ack = 1;
    struct sockaddr_in serveraddr;
    char n[5];
    socklen_t len = sizeof(serveraddr);
    Frame Frame_send;
    Frame Frame_recv;
    printf("Creating Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Enter Number of Frames: ");
    scanf("%s", n);
    printf("Sending Number of Frames!\n");
    sendto(socket_udp, n, sizeof(n), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    while(frame_id < atoi(n)) {
        if(ack == 1) {
            Frame_send.sq_no = frame_id;
            Frame_send.frame_kind = 0;
            Frame_send.ack = 0;
            printf("Enter Data for Frame %d: ", frame_id);
            scanf("%s", Frame_send.packet.data);
        }
        sendto(socket_udp, &Frame_send, sizeof(Frame_send), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        recvfrom(socket_udp, &Frame_recv, sizeof(Frame_recv), 0, (struct sockaddr *)&serveraddr, &len);
        if(Frame_recv.sq_no == frame_id+1 && Frame_recv.frame_kind == 0 && Frame_recv.ack == 1) {
            printf("Ack Received!\n");
            ack = 1;
            frame_id++;
        } else {
            printf("Ack Not Received!\n");
            ack = 0;
        }
    }
    close(socket_udp);
    return 0;
}