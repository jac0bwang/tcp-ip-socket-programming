#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 	1024
void error_handling(char *message);

int main(int argc, char *argv[]){
	int serv_sock;
	int clnt_sock;

	char message[BUF_SIZE] = "This message is sent from the server!!";
	int str_len,i;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	
	if(argc != 2){
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock == -1){
		error_handling("socket() error");
	}

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1){
		error_handling("bind() error");
	}

	if(listen(serv_sock,5) == -1){
		error_handling("listen() error");
	}

	clnt_addr_size = sizeof(clnt_addr);
	for(i=0;i<5;i++){
		clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
		if(clnt_sock == -1){
			error_handling("accept() error");
		}else{
			printf("Connected client %d\n",i+1);
		}
		printf("The message from Server is %s\n:",message);
			write(clnt_sock,message,strlen(message)+1);//仅进行数据发送，不进行接收，为了验证TCP三次握手中不会丢失数据
			                                 //详情应看客户端输出是否等于服务器端
		close(clnt_sock);
	}
	close(serv_sock);

	return 0;

}

void error_handling(char *message){

	fputs(message,stderr);
	fputs("\n",stderr);
	exit(1);
}
