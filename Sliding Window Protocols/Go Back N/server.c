#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

struct frame {
    int packets[40];
}Frame;

struct acknowledgement {
    int acknowledge[40];
}Acknowledgement;

int main() {
    int socket_udp, port, windowsize, totalpackets = 10, i = 0, frame = 0, j, flag;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    printf("Creating UDP Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);
    printf("Binding...\n");
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, (char *)&windowsize, sizeof(windowsize), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Received Windowsize from Client\n");
    printf("Retreiving Total Packets from Network Layer...\n");
    printf("Total Packets: %d\n", 10);
    sendto(socket_udp, (char *)&totalpackets, sizeof(totalpackets), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Starting Transmission of Packets...\n");
    while(i < totalpackets) {
        j = 0;
        while(j < windowsize && j < totalpackets) {
            Frame.packets[j] = i;
            j++;
            i++;
        }
        printf("Sending Frame %d\n", frame);
        sendto(socket_udp, (char *)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        recvfrom(socket_udp, (char *)&Acknowledgement, sizeof(Acknowledgement), 0, (struct sockaddr *)&serveraddr, &len);
        j = 0;
        flag = 0;
        while(j < windowsize && j < totalpackets) {
            if(Acknowledgement.acknowledge[j] == -1) {
                printf("Negative Acknowledgement Received fot Packet %d!\n", Frame.packets[j]);
                i = Frame.packets[j];
                frame++;
                flag = 1;
                break;
            }
            j++;
        }
        if(flag != 1) {
            printf("All Packets in Frame Received Successfully!\n");
            frame++;
        } 
    }
    printf("Transmission Complete!\n");
    close(socket_udp);
    return 0;
}