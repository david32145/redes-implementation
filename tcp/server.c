#include <stdio.h> 
#include <stdlib.h>

#include <string.h>

#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

#define MAX 80
#define MAX_SIZE_CLIENTS 5
#define PORT 8080 
#define SA struct sockaddr 
#define TRUE 1


void serverListen(int connectionStatus){
    char messageBuffer[MAX];
    char tmp[MAX];
    while (TRUE){
        bzero(messageBuffer, MAX);
        read(connectionStatus, messageBuffer, sizeof(messageBuffer));
        printf("Cliente de nome %s enviou uma messagem.\n", messageBuffer);
        strncpy(tmp, messageBuffer, strlen(messageBuffer));
        sprintf(messageBuffer, "Olá %s bem vindo!!!", tmp);
        write(connectionStatus, messageBuffer, sizeof(messageBuffer));
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
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    int bindStatus = bind(socketStatus, (SA*)&serverAddress, sizeof(serverAddress));
    if(bindStatus == 0){
        printf("Socket binded in localhost:%d\n", PORT);
    } else {
        printf("Cannot bind socket to host...\n");
    }

    int listenStatus = listen(socketStatus, MAX_SIZE_CLIENTS);
    if(listenStatus == 0){
        printf("Server is running in tcp://localhost:%d\n", PORT);
    } else {
        printf("Error on listen server...");
        exit(0);
    }

    int len = sizeof(client);
    int connectionStatus = accept(socketStatus, (SA*)&client, &len);

    if(connectionStatus < 0) {
        printf("Cannot accepted the client....\n");
        exit(0);
    } else {
        printf("Client accepted with successful...\n");
    }

    serverListen(connectionStatus);

    close(socketStatus);
    return 0;
}
