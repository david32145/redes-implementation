#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> //para close()

#include <sys/types.h> //AF_INET
#include <sys/socket.h>
#include <netinet/in.h> //htons()
/*
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
*/

#define PORT 5000
#define MESSAGE_LENGTH 80
#define SERVER_ADRESS_IP "127.0.0.1"

int main() {
    
    struct sockaddr_in serverAddress, client;
    int socketLocalClient;
    int client_len = sizeof(client);
    char message[MESSAGE_LENGTH], *nameClient, *nameServer;
    
    printf("Iniciando Cliente ...\n");

    /* Cria um socket para o cliente */
    socketLocalClient = socket(AF_INET, SOCK_DGRAM, 0);
    if ( socketLocalClient == -1) {
        printf("Erro na criação de socket do cliente:");
        exit(0);
    }
    printf("Socket do Cliente criado: %d\n", socketLocalClient);

    
    /* Define as propriedades da conexão  */
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;//memset(serverAddress.sin_zero, 0x0, 8);
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_ADRESS_IP);

    /* Tenta se conectar ao serverAddress
    int connectionStatus = connect(socketLocalClient, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if ( connectionStatus == -1) {
        printf("Não foi possivel conectar ao Servidor");
        exit(0);
    }
    */
    
    int n= 0;
    bzero(message, sizeof(message));
    printf("Digite seu nome: ");
    scanf("%[^\n]s",message);
    strcpy(message,"\nOla Servidor!");
    write(socketLocalClient, message, sizeof(message));
    bzero(message, sizeof(message));
    read(socketLocalClient, message, sizeof(message));
    printf("Servidor disse: %s\n", message);



    close(socketLocalClient);
    printf("\nConnection closed\n\n");

    

    return 0;


}
