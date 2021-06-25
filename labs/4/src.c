#include <stdio.h>
#include <pthread.h>

#define NTHREADS 4

int x;

pthread_mutex_t lock;
pthread_cond_t cond;

void *t1(void *arg){
    
    pthread_mutex_lock(&lock);
    while(x != 3){
        pthread_cond_wait(&cond, &lock);
    }
    puts("Volte sempre!");
    pthread_mutex_unlock(&lock);    

    pthread_exit(NULL);
}

void *t2(void *arg){
    pthread_mutex_lock(&lock);
    if(x == 0){
        pthread_cond_wait(&cond, &lock);
    }
    x++;
    puts("Fique a vontade.");
    pthread_cond_signal(&cond);    
    pthread_mutex_unlock(&lock);  

    pthread_exit(NULL);
}

void *t3(void *arg){
    pthread_mutex_lock(&lock);
    if(x == 0){
        pthread_cond_wait(&cond, &lock);
    }
    x++;
    puts("Sente-se por favor.");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);    

    pthread_exit(NULL);
}

void *t4(void *arg){
    pthread_mutex_lock(&lock);
    x++;
    puts("Seja bem-vindo!");
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);   

    pthread_exit(NULL);
}

int main(){

    pthread_t tid[NTHREADS];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&tid[0], NULL, t1, NULL);
    pthread_create(&tid[1], NULL, t2, NULL);
    pthread_create(&tid[2], NULL, t3, NULL);
    pthread_create(&tid[3], NULL, t4, NULL);

    for (int i = 0; i < NTHREADS; i++){
        pthread_join(tid[i], NULL);
    }
    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);


}