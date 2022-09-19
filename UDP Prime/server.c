#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>

int primeCheck(int n) {
    if(n == 2) {
        return 1;
    }
    int i;
    for(i = 2; i < n/2; i++) {
        if(n%i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int socket_udp, port, n, prime;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(socket_udp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    recvfrom(socket_udp, (char *)&n, sizeof(n), 0, (struct sockaddr *)&serveraddr, &len);
    prime = primeCheck(n);
    sendto(socket_udp, (char *)&prime, sizeof(prime), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Result Sent to Client!\n");
    close(socket_udp);
    return 0;
}