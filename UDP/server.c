#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int socket_udp, port;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    char message[50];
    printf("Creating UDP Socket!\n");
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding!\n");
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr *)&serveraddr, &len);
    printf("Received Message %s\n");
    sendto(socket_udp, "YOUR MESSAGE IS RECEIVED", sizeof("YOUR MESSAGE IS RECEIVED"), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Message sent to Client!\n");
    close(socket_udp);
    return 0;
}