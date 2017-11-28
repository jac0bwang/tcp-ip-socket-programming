#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

#define BUFFSIZE 64

void errorHandling(const char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void removeChild(int signo)
{
    int status = 0;

    pid_t pid = waitpid(-1, &status, WNOHANG);
    
    printf("remove child process: pid = %d \n", pid);
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    struct sigaction act;
    act.sa_handler = removeChild;
    act.sa_flags   = 0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD,&act, 0);

    int serv_sock, clnt_sock;

    sockaddr_in addrServ, clnt_adr;

    memset(&addrServ, 0, sizeof(addrServ));
    addrServ.sin_family         = AF_INET;
    addrServ.sin_addr.s_addr    = htonl(INADDR_ANY);
    addrServ.sin_port           = htons(atoi(argv[1]));         

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(0 != bind(serv_sock, (struct sockaddr*)&addrServ, sizeof(addrServ))){
        errorHandling("bind() error!");
    }

    if(0 != listen(serv_sock, 5)){
        errorHandling("listen() error!");
    }

    socklen_t adr_sz = sizeof(clnt_adr);
    while(1){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
        if(clnt_sock == -1){
            continue;
        }
        else{
            puts("new client connected...");
        }

        pid_t pid = fork();

        if(pid == -1){
            close(clnt_sock);
            continue;
        }

        if(pid == 0){
			close(serv_sock);
            
            char buf[BUFFSIZE];
            int receivedByte = 0;
            while((receivedByte = read(clnt_sock,buf, sizeof(buf)))>0){
                write(clnt_sock, buf, receivedByte);
            }

            close(clnt_sock);

            puts("client disconnected...");

            return 0;
        }
        else
            close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}