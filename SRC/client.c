#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
	int clientSocket, portNum, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);//插上插座

	serverAddr.sin_family = AF_INET;//TCP本機連線
	serverAddr.sin_port = htons(7891);//設定port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//設定IP
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);//撥號碼 打給server

	while(1){
		printf("Type a sentence to send to server:\n");
		fgets(buffer,1024,stdin);
		printf("You typed: %s",buffer);

		nBytes = strlen(buffer) + 1;

		send(clientSocket,buffer,nBytes,0);//對server講話
	}

	return 0;
} 
