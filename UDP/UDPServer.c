#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> //para close()

#include <sys/types.h> //AF_INET
#include <sys/socket.h>
#include <netinet/in.h> //htons()

#define PORT 5000
#define MESSAGE_LENGTH 80
#define NUM_MAX_CONEXAO_CLIENTS 2

int main() {

	struct sockaddr_in client, serverAddress;
	int socketServer, statusConnectionClient;
	socklen_t client_len = sizeof(client); 
    char message[MESSAGE_LENGTH], *nameServer, *nameClient, *messageClient;
    nameServer = "Google";

	printf("\nIniciando Servidor %s...",nameServer);
	socketServer = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketServer == -1){
		printf("\nSocket não criado!!!");
		exit(0);
	} else
		printf("\nSocket do Servidor criado");

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //escolhe a porta que estiver livre
    serverAddress.sin_port = htons(PORT); //host to network short

    /* Liga a porta ao socket. */
	int statusBind = bind(socketServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (statusBind == -1 ) {
        printf("\nNão foi possivel associa o socket a porta...\n");
        exit(0);
    } else
		printf("\nSocket associado a porta:%d\n", PORT);
    
	/*  Habilita o socket para receber as conexões 
    int a = listen(socketServer, NUM_MAX_CONEXAO_CLIENTS);
    if( a == -1) {
        printf("\nErro na escuta do servidor\n");
        exit(0);
    }else
        printf("\nServidor está executando em UDP: //120.0.0.1: %d\n", PORT);
    */
	/*Aceitar as conexões
	statusConnectionClient = accept(socketServer,(struct sockaddr *) &client, (socklen_t*)&client_len);
    if (statusConnectionClient < 0) {
        printf("\nNão foi possivel aceitar a conexão.\n");
        exit(0);
    } else
		printf("\nCliente aceito");
    */
    do {
       // memset(message, 0, MESSAGE_LENGTH);
        //recvfrom(statusConnectionClient, message, MESSAGE_LENGTH, 0, (struct sockaddr*)&client, &client_len);
        recvfrom(socketServer, message, MESSAGE_LENGTH, 0, (struct sockaddr*)&client, &client_len);
        
        nameClient = strtok(message, "\n");
        messageClient = strtok('\0', "/0");
        printf("\nO Cliente %s, enviou a mensagem: %s\n",nameClient, messageClient);

        memset(message, 0, MESSAGE_LENGTH);
        strcat(message,nameServer);
        strcat(message,"\n");
        strcat(message,messageClient);
        write(statusConnectionClient, message, sizeof(message));
	    sendto(statusConnectionClient, message, strlen(message), 0, (struct sockaddr*)&client ,sizeof(client));
    } while(1);

    /*
        => A aplicação cliente deverá informar seu nome e uma mensagem à servidora.
        => A servidora deverá imprimir a mensagem recebida e retornar seu nome e
        uma mensagem à cliente. 
        =>A cliente também deverá imprimir a mensagem.
    */

    close(statusConnectionClient);
    close(socketServer);
    printf("Conexão fechada\n\n");

    return 0;
}