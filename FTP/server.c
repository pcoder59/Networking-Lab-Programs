#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int main () {
    FILE *fp;
    int socket_tcp, client_socket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char filename[100], contents[1024];
    printf("Creating TCP Socket!\n");
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Listening...\n");
    listen(socket_tcp, 5);
    client_socket = accept(socket_tcp, (struct sockaddr *)&clientaddr, &len);
    read(client_socket, filename, sizeof(filename));
    fp = fopen(filename, "r");
    if(fp == NULL) {
        write(client_socket, "Error", sizeof("Error"));
        printf("Error");
    }else {
        if(!fgets(contents, sizeof(contents), fp)) {
            write(client_socket, "Error", sizeof("Error"));
            printf("Error");
        } else {
            printf("%s\n", contents);
            write(client_socket, contents, sizeof(contents));
        }
    }
    close(socket_tcp);
    close(client_socket);
    fclose(fp);
    return 0;
}