#include<pthread.h>

int x=0, y=0; //variaveis globais
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *T1(void *id){
    int a=0;
    while(a<2) {       
        if(x==0){
            printf("x=%d\n",x);
        }
        a++;        
        printf("a=%d\n", a); 
    }
}

void *T2(void *id){
    int a=2;
    while(a>0){
        if(x==0){
            printf("x=%d\n",x);
        }
        a--; 
        fprintf(file,"a=%d\n", a);
    } 
}

void *T3(void *id){
    pthread_mutex_lock(&lock);         
    x--;
    x++;
    pthread_mutex_unlock(&lock);
    y++;
}

