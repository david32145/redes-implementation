#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 8080 
#define TAM_MAX 200 

void error(char *msg){
	printf("%s\n",msg);
	exit(0);
}

int main() { 
	struct sockaddr_in serverAddress; 
	int sockfd;
	char *messageSend = "Ola Servidor eu sou o Cliente 123";
	char messageReceived[TAM_MAX];  

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sockfd < 0 ) 
		error("Socket não foi criado!\n"); 

	bzero(&serverAddress, sizeof(serverAddress));  
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(PORT); 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	
	int length_RecvFrom, len; 

	sendto(sockfd, messageSend, strlen(messageSend), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)); 

	length_RecvFrom = recvfrom(sockfd, messageReceived, TAM_MAX, 0, (struct sockaddr *)&serverAddress, &len); 
	messageReceived[length_RecvFrom] = '\0'; 
	printf("Mensagem Recebida: %s\n",messageReceived);

	close(sockfd); 
	return 0; 
}