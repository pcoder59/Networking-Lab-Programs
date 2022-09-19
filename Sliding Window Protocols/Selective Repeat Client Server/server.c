#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

struct frame {
    int packets[50];
}Frame;

struct acknowledge {
    int acknowledge[50];
}Acknowledgement;

int main() {
    int socket_udp, port, windowsize, totalframes, i, j;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, (char *)&totalframes, sizeof(totalframes), 0, (struct sockaddr *)&serveraddr, &len);
    recvfrom(socket_udp, (char *)&windowsize, sizeof(windowsize), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Enter Data For Each Frame: ");
    for(i = 0; i < totalframes; i++) {
        scanf("%d", &Frame.packets[i]);
    }
    i = 0;
    while(i < totalframes) {
        j = i;
        printf("Sending Frames in Window...\n", i+1);
        while(j < windowsize + i && j < totalframes) {
            printf("Sending Packet %d\n", j+1);
            j++;
        }
        sendto(socket_udp, (char *)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        recvfrom(socket_udp, (char *)&Acknowledgement, sizeof(Acknowledgement), 0, (struct sockaddr *)&serveraddr, &len);
        j = i;
        while(j < windowsize + i && j < totalframes) {
            if(Acknowledgement.acknowledge[j] == -1) {
                printf("Acknowledgement Negative for Packet %d\n", j+1);
                printf("Resending the Packet...\n");
            }
            j++;
        }
        sendto(socket_udp, (char *)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        printf("All Packets in Window sent Successfully!\n");
        i = i + windowsize;
    }
    printf("All Frames Sent Successfully!\n");
    close(socket_udp);
    return 0;
}