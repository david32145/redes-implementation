#include <stdio.h> 
#include <stdlib.h>

#include <string.h>

#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

#define MAX 80
#define PORT 8080 
#define SA struct sockaddr 
#define TRUE 1


void clientListen(int connectionStatus){
    char messageBuffer[MAX];
    while (TRUE){
        int n =0;
        bzero(messageBuffer, sizeof(messageBuffer));
        printf("Digite seu nome: ");
        while((messageBuffer[n++] = getchar()) != '\n') {}
        messageBuffer[n-1] = '\0';
        write(connectionStatus, messageBuffer, sizeof(messageBuffer));
        bzero(messageBuffer, sizeof(messageBuffer));
        read(connectionStatus, messageBuffer, sizeof(messageBuffer));
        printf("Servidor disse: %s\n", messageBuffer);
    }
}

int main(int argc, char const *argv[])
{
    int socketStatus;

    struct sockaddr_in serverAddress, client;

    socketStatus = socket(AF_INET, SOCK_STREAM, 0);
    if(socketStatus != -1){
        printf("Socket created...\n");
    } else {
        printf("Unspected error on socket connection...\n");
        exit(0);
    }

    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(PORT);

    int connectionStatus = connect(socketStatus, (SA*)&serverAddress, sizeof(serverAddress));
    if(connectionStatus == 0){
        printf("Socket connected in localhost:%d\n", PORT);
    } else {
        printf("Cannot connect to host...\n");
        exit(0);
    }

    clientListen(socketStatus);

    close(connectionStatus);
    return 0;
}
