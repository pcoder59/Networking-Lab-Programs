#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main() {
    int socket_udp, port;
    struct sockaddr_in serveraddr;
    char message[50], send[50];
    socklen_t len;
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    printf("Binding...\n");
    bind(socket_udp, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    len = sizeof(serveraddr);
    sendto(socket_udp, "mesg: SMTP REQUEST FROM CLIENT", sizeof("mesg: SMTP REQUEST FROM CLIENT"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    sendto(socket_udp, "HELLO name_of_client_mail_server", sizeof("HELLO name_of_client_mail_server"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    printf("Enter From Address: ");
    scanf("%s", message);
    sendto(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    printf("Enter To Address: ");
    scanf("%s", message);
    sendto(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    printf("Enter Email, End with .");
    while(strcmp(message, ".") != 0) {
        scanf("%s", message);
        sendto(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    }
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    sendto(socket_udp, "QUIT", sizeof("QUIT"), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("S: %s\n", message);
    close(socket_udp);
    return 0;
}