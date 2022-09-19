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
    int socket_udp, port, windowsize, totalframes, i, j, flag;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    printf("Binding...\n");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter Total Number of Frames: ");
    scanf("%d", &totalframes);
    sendto(socket_udp, (char *)&totalframes, sizeof(totalframes), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter Window Size: ");
    scanf("%d", &windowsize);
    sendto(socket_udp, (char *)&windowsize, sizeof(windowsize), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    i = 0;
    while(i < totalframes) {
        flag = 0;
        j = i;
        printf("Receiving From Server...\n");
        recvfrom(socket_udp, (char *)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, &len);
        while(j < i + windowsize && j < totalframes) {
            printf("Enter Acknowledgement, -1 for Negative Acknowledgement: ");
            scanf("%d", &Acknowledgement.acknowledge[j]);
            if(Acknowledgement.acknowledge[j] == -1) {
                flag = 1;
            }
            j++;
        }
        sendto(socket_udp, (char *)&Acknowledgement, sizeof(Acknowledgement), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if(flag == 1) {
            printf("Receiving Packets With Negative Acknowledgement...\n");
            recvfrom(socket_udp, (char*)&Frame, sizeof(Frame), 0, (struct sockaddr *)&serveraddr, &len);
            printf("Received Packets With Negative Acknowledgement...\n");
        }
        printf("All Packets Are Received Successfully!\n");
        i = i + windowsize;
    }
    printf("All Frames Sent Successfully!\n");
    close(socket_udp);
    return 0;
}