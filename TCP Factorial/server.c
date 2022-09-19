#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int factorial(int i) {
    if(i == 1) {
        return 1;
    }
    return i * factorial(i-1);
}

int main() {
    int socket_tcp, client_tcp, port, num, fact;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(socket_tcp, 5);
    client_tcp = accept(socket_tcp, (struct sockaddr *)&clientaddr, &len);
    read(client_tcp, (char *)&num, sizeof(num));
    fact = factorial(num);
    write(client_tcp, (char *)&fact, sizeof(fact));
    printf("Factorial Sent to Client Successfully!\n");
    close(socket_tcp);
    return 0;
}