#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main () {
    int socket_tcp, client_tcp, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char message[50];
    printf("Creating TCP Socket!\n");
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);
    printf("Binding Port!\n");
    bind(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Start Listening...\n");
    listen(socket_tcp, 5);
    client_tcp = accept(socket_tcp, (struct sockaddr *)&clientaddr, &len);
    printf("Client Connection Received!\n");
    read(client_tcp, message, sizeof(message));
    printf("Client Sent: %s\n", message);
    write(client_tcp, "YOUR MESSAGE IS RECEIVED", sizeof("YOUR MESSAGE IS RECEIVED"));
    printf("Sent Message to Client!\n");
    close(socket_tcp);
    close(client_tcp);
    return 0;
}