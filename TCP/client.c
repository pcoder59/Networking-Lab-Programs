#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main() {
    int client_tcp, port;
    struct sockaddr_in serveraddr;
    char message[50];
    printf("Creating TCP Socket!\n");
    client_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding to Port!\n");
    bind(client_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Connecting to TCP Server!\n");
    connect(client_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Sending Message!\n");
    send(client_tcp, "HI I AM CLIENT", sizeof("HI I AM CLIENT"), 0);
    recv(client_tcp, message, sizeof(message), 0);
    printf("Received Message %s\n", message);
    close(client_tcp);
    return 0;
}