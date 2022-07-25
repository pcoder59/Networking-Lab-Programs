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
    int socket_udp, port, windowsize, totalpackets, i = 0, frame = 0, j, flag, ack;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    printf("Creating UDP Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Enter Window Size: ");
    scanf("%d", &windowsize);
    printf("Sending Window Size...\n");
    sendto(socket_udp, (char *)&windowsize, sizeof(windowsize), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, (char *)&totalpackets, sizeof(totalpackets), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Total Packets: %d\n", totalpackets);
    while(i < totalpackets) {
        printf("Expected frame is %d with packets: ", frame);
        for(j = i; j < i + windowsize; j++) {
            if(j < totalpackets) {
                printf("%d ", j);
            }
        }
        recvfrom(socket_udp, (char *)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, &len);
        printf("\nPackets Received! Acknowledge Each!\n");
        flag = 0;
        for(j = 0; j < windowsize; j++) {
            if(j < totalpackets) {
                printf("Packet %d\n", Frame.packets[j]);
                printf("Enter -1 to Send Negative Acknowledgement: \n");
                scanf("%d", &ack);
                if(ack == -1) {
                    Acknowledgement.acknowledge[j] = -1;
                    i = Frame.packets[j];
                    flag = 1;
                    frame++;
                    break;
                } else {
                    Acknowledgement.acknowledge[j] = 1;
                }
            }
        }
        if(flag != 1) {
            printf("All Packets Acknowledged!\n");
            i = i + windowsize;
            frame++;
        }
        sendto(socket_udp, (char *)&Acknowledgement, sizeof(Acknowledgement), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    }
    printf("Transmission Complete!\n");
    close(socket_udp);
    return 0;
}