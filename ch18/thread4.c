#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREAD 100

long long sum = 0;

void* thread_inc(void* arg){
    for(int i=0;i<50000000;i++){
        sum+=1;
    }
    return NULL;
}

void* thread_des(void* arg){
    for(int i=0;i<50000000;i++){
        sum-=1;
    }
    return NULL;
}

int main(){
    pthread_t t_id[NUM_THREAD];

    for(int i=0;i<NUM_THREAD;i++){
        if(i%2 == 0){
            pthread_create(&t_id[i], NULL, thread_inc, NULL);
        }
        else{
            pthread_create(&t_id[i], NULL, thread_des, NULL);
        }
    }

    for(int i=0;i<NUM_THREAD;i++){
        pthread_join(t_id[i], NULL);
    }

    //printf("sizeof(long long): %d \n", sizeof(long long));
    printf("sum: %lld \n", sum);

    return 0;
}