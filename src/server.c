#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int socketfd, newSocket, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	int i;

	socketfd = socket(PF_INET, SOCK_STREAM, 0);//插上插座
	  
	serverAddr.sin_family = AF_INET;//TCP本機傳輸
	serverAddr.sin_port = htons(7891);//設定port
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//設定IP
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	bind(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));//接上電話線

	if(listen(socketfd,5)==0)//聽頻道上有無client要連線->電話響了 拿起聽筒
		printf("Listening\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;

	while(1){
		newSocket = accept(socketfd, (struct sockaddr *) &serverStorage, &addr_size);//接受連線->聽client說話
		   
		if(!fork()){//創child process處理連線
			nBytes = 1;
			while(nBytes!=0){//連線中利用while loop連續處理字串接收
				nBytes = recv(newSocket,buffer,1024,0);//接收client傳來的資料
				printf("%s",buffer);//印出收到的資料
			}
			close(newSocket);//關閉socket連線並等待下一個連線->掛電話
			exit(0);
		}
		else{//若child process結束 parent接收 並關閉socket 等待下一個連線作業
			close(newSocket);
		}
	}

	return 0;
} 
