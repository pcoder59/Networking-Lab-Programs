#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main() {
    FILE *fp;
    int socket_tcp, port;
    struct sockaddr_in serveraddr;
    char filename[100], newfile[100], contents[1024];
    printf("Creating TCP Socket!\n");
    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter Port Number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    connect(socket_tcp, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter File Name: ");
    scanf("%s", filename);
    printf("Enter New File Name: ");
    scanf("%s", newfile);
    fp = fopen(newfile, "w");
    send(socket_tcp, filename, sizeof(filename), 0);
    recv(socket_tcp, contents, sizeof(contents), 0);
    if(strcmp("Error", newfile) == 0) {
        printf("Error");
    } else {
        printf("Contents Received: %s\n", contents);
        fprintf(fp, "%s", contents);
    }
    close(socket_tcp);
    fclose(fp);
    return 0;
}