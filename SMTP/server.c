#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main() {
    int socket_udp, port;
    struct sockaddr_in serveraddr;
    char message[100], send[100];
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
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("%s\n", message);
    sendto(socket_udp, "220 name_of_server_mail_server", sizeof("220 name_of_server_mail_server"), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("C: %s\n", message);
    sprintf(send, "250 Hello %s", message);
    sendto(socket_udp, send, sizeof(send), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("C: MAIL FROM: <%s>\n", message);
    sprintf(send, "250 Hello <%s> ... Sender OK", message);
    sendto(socket_udp, send, sizeof(send), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("C: RCPT TO: <%s>\n", message);
    sprintf(send, "250 Hello <%s> ... Receipient OK", message);
    sendto(socket_udp, send, sizeof(send), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    while(strcmp(message, ".") != 0) {
        printf("%s\n", message);
        recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    }
    sendto(socket_udp, "250 Message Accepted for Delivery", sizeof("Message Accepted for Delivery"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("C: %s\n", message);
    sendto(socket_udp, "221 Server Mail Server Closing Connection", sizeof("Server Mail Server Closing Connection"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    close(socket_udp);
    return 0;
}