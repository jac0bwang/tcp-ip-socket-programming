#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void child_handler(int signo){
    if(signo == SIGCHLD){
        int status = 0;
        pid_t pid = waitpid(-1, &status, WNOHANG);

        if(WIFEXITED(status)){
            printf("Removed process pid: %d \n", pid);
            printf("child send: %d \n", WEXITSTATUS(status));
        }
    }
}

int main()
{
    struct sigaction act;
    act.sa_handler = child_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();
    if(pid == 0){
        puts("I'm child process");
        sleep(10);
        puts("child process will exit");
        return 12;
    } else {
        printf("fork() child pid: %d \n", pid);
		
		pid = fork();
		
		if (pid == 0) {
			puts("Hi! I'm child process");
			sleep(20);
			exit(24);
		} else {
			int i;
			printf("Child proc id : %d\n", pid);
			for (i = 0; i < 5; i++) {
				puts("wait....");
				sleep(5);
			}
		}
		
	}

    return 0;
}
