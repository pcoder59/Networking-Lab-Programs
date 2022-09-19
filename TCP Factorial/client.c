#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int socket_tcp, port, n;
    struct sockaddr_in serveraddr;
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    connect(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter Number: ");
    scanf("%d", &n);
    send(socket_tcp, (char *)&n, sizeof(n), 0);
    recv(socket_tcp, (char *)&n, sizeof(n), 0);
    printf("Factorial of Number is: %d\n", n);
    close(socket_tcp);
    return 0;
}