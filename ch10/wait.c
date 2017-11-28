#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int status = 0;
    pid_t pid = fork();

    if(pid == 0) {
        return 3;
    } else {
        printf("child pid: %d \n", pid);

        pid_t pid = fork();

        if (pid == 0){
            exit(7);
        }
        else{
            printf("child pid: %d \n", pid);         
            wait(&status);
            if(WIFEXITED(status)){
                printf("child send: %d \n", WEXITSTATUS(status));
            }

            wait(&status);
            if(WIFEXITED(status)){
                printf("child send: %d \n", WEXITSTATUS(status));
            }
            sleep(30); //Sleep 30 sec.
        }
    }

    return 0;
}   