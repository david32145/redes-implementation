#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define TAM_MAX  1024 

void error(char *msg){
	printf("%s\n",msg);
	exit(0);
}

int main() { 
	struct sockaddr_in serverAddress, clientAddress; 
	int sockfd; 
	char messageReceived[TAM_MAX];
	char *messageSend= "Ola Cliente, eu sou o Servidor!"; 
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sockfd < 0 ) 
		error("Não foi possivel criar o socket!\n"); 

	bzero(&serverAddress, sizeof(serverAddress));  

	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	serverAddress.sin_port = htons(PORT);  
	
	int statusBind = bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if ( statusBind < 0 )
		error("A operação de bind falhou!\n");
	
	int lenght_clientAddress, length_RecvFrom; 
	lenght_clientAddress = sizeof(clientAddress); 

	length_RecvFrom = recvfrom(sockfd, messageReceived, TAM_MAX, 0, (struct sockaddr *)&clientAddress, &lenght_clientAddress); 
	messageReceived[length_RecvFrom] = '\0'; 
	printf("Mensagem Recebida: %s\n", messageReceived);

	sendto(sockfd, messageSend, strlen(messageSend), 0, (struct sockaddr *) &clientAddress, lenght_clientAddress);
	
	return 0; 
} 
