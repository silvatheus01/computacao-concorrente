#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
#define P 10
#define C 10
#define TEMPO 1

//Guarda os itens.
int buf[N];

// Flags para saber se um consumidor específico já consumiu aquele item da lista
int count[N][C];

// Número de itens existentes na lista
int n = 0;

// Posição da próxima inserção de um item
int in = 0; 

// Posição da próxima retirada de um item
int out = 0;

// Semáforos binários
sem_t prod_t, cons_t;

int retira(int id){
    sem_wait(&cons_t);
    // Se não há itens, um produtor deve produzir antes que alguém consuma.
    while(n == 0){
        sem_post(&prod_t);
        sem_wait(&cons_t);
    } 
    int aux = 0;

    // Marca que o consumidor vai consumir aquela posição no buffer
    count[out][id] = 1;

    for (int i = 0; i < C; i++){
        //Checa se todos os consumidores já consumiram...
        if(count[out][i] == 1) aux++;
        //.. Se não consumiu, não retira do buffer...
        else{
            aux = -1;
            break;
        } 
    }
    
    // .. Mas se todas as posições são iguais a 1, então todos os consumidores já consumiram
    // então o item pode ser retirado do buffer
    if(aux == C){
        for (int i = 0; i < C; i++){
            // Zera as flags
            count[out][i] = 0;
        }
        aux = buf[out];
        // Retira o item do buffer
        buf[out] = 0;
        out = (out + 1) % N;
        n--;
    }    
    
    sem_post(&prod_t);
    sem_post(&cons_t);

    return aux;

}

void insere(int item){
    sem_wait(&prod_t);
    // Se o buffer esta cheio, um consumidor deve consumir antes de alguem produzir
    while(n == N){
        sem_post(&cons_t);
        sem_wait(&prod_t);
    }

    // Se a posição atual do buffer esta ocupada, o programa tenta a próxima
    while(buf[in] != 0){
        in = (in + 1) % N;
        // Permite que consumidores esvaziem espaço no buffer
        sem_post(&cons_t);
        sem_wait(&prod_t);
    } 

    buf[in] = item; 
    in = (in + 1) % N;  
    n++;
    sem_post(&cons_t);
    sem_post(&prod_t);
}

void *prod(void *arg){
    int *id = (int*) arg;
    while(1){
        printf("Produtor %d quer produzir.\n", *id);
        // Cada produtor insere o seu próprio ID no buffer
        insere(*id);
        printf("Produtor %d produziu.\n", *id);
        sleep(TEMPO);
    }
    pthread_exit(NULL);
}

void *cons(void *arg){
    int *id = (int*) arg;
    int item;
    while(1){
        printf("Consumidor %d quer consumir.\n", *id);
        // O ID serve para checar as flags
        item = retira(*id);
        if(item == -1){
            printf("Consumidor %d não consumiu.\n", *id);
        }else{
            printf("Consumidor %d consumiu o item %d.\n", *id, item);
        }
        
        sleep(TEMPO);
    }
    pthread_exit(NULL);

}


int main(){

    sem_init(&prod_t, 0, 1);
    sem_init(&cons_t, 0, 1);

    pthread_t tid_prod[P];
    pthread_t tid_cons[C];

    for (int i = 0; i < C; i++){
        int *id = (int*) malloc(sizeof(int));
        *id = i;
        pthread_create(&tid_cons[i], NULL, cons, (void*) id);
    }

    for (int i = 0; i < P; i++){
        int *id = (int*) malloc(sizeof(int));
        *id = i;
        pthread_create(&tid_prod[i], NULL, prod, (void*) id);
    }

    pthread_exit(NULL);
    

}