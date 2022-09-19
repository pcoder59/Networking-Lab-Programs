#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int socket_udp, port, n;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter a Number: ");
    scanf("%d", &n);
    sendto(socket_udp, (char *)&n, sizeof(n), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, (char *)&n, sizeof(n), 0, (struct sockaddr *)&serveraddr, &len);
    if(n == 0) {
        printf("The Number is Not Prime!\n");
    } else {
        printf("Prime Number!\n");
    }
    close(socket_udp);
    return 0;
}