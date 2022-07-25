#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int socket_udp, port;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    char message[50];
    printf("Creating a UDP Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    printf("Binding Port!\n");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Sending Message!\n");
    sendto(socket_udp, "HI I AM CLIENT", sizeof("HI I AM CLIENT"), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Received Message %s\n");
    close(socket_udp);
    return 0;
}