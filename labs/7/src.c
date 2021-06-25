#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define NTHREADS 4

sem_t cond_meio, cond_final;

void *t1(void *arg){
    
    sem_wait(&cond_final);
    sem_post(&cond_meio);
    sem_wait(&cond_final);
    sem_post(&cond_meio);
    sem_wait(&cond_final);

    puts("Volte sempre!");     

    pthread_exit(NULL);
}

void *t2(void *arg){
    
    sem_wait(&cond_meio);
    puts("Fique a vontade.");
    sem_post(&cond_final);

    pthread_exit(NULL);
}

void *t3(void *arg){

    sem_wait(&cond_meio);
    puts("Sente-se por favor."); 
    sem_post(&cond_final);

    pthread_exit(NULL);
}

void *t4(void *arg){

    puts("Seja bem-vindo!");
    sem_post(&cond_final); 

    pthread_exit(NULL);
}

int main(){

    pthread_t tid[NTHREADS];  

    sem_init(&cond_meio, 0, 0);
    sem_init(&cond_final, 0, 0);
    
    pthread_create(&tid[0], NULL, t1, NULL);
    pthread_create(&tid[1], NULL, t2, NULL);
    pthread_create(&tid[2], NULL, t3, NULL);
    pthread_create(&tid[3], NULL, t4, NULL);

    for (int i = 0; i < NTHREADS; i++){
        pthread_join(tid[i], NULL);
    }
    
    sem_destroy(&cond_meio);
    sem_destroy(&cond_final);

}