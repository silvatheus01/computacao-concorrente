#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "matriz.h"

#define VDEFAULT 2

#define GET_TIME(now) { \
   struct timespec time;\
   clock_gettime(CLOCK_MONOTONIC, &time);\
   now = time.tv_sec + time.tv_nsec/1000000000.0;\
}

int main(int agrc, char **agrv){
    if(agrc < 3){
        puts("Falta argumentos na entrada");
        exit(-1);
    }

    // A função strtol transforma uma string em um número
    long nthreads = strtol(agrv[1], NULL, 10);
    long dim = strtol(agrv[2], NULL, 10);

    // nthreads <= dim deve ocorrer sempre para evitar erros
    if(nthreads > dim) {
        nthreads = dim;
    }else if (nthreads <= 1){
        nthreads = 1;
    }

    // Responsáveis pela contagem do tempo de processamento
    double inicial_t, final_t, total_t;
    GET_TIME(inicial_t);

    pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);

    Matriz *m1, *m2, *mr;

    m1 = (Matriz *) malloc(sizeof(Matriz));
    m2 = (Matriz *) malloc(sizeof(Matriz));
    mr = (Matriz *) malloc(sizeof(Matriz));

    fillm(m1, dim, VDEFAULT);
    fillm(m2, dim, VDEFAULT);
    fillm(mr, dim, 0);    

    GET_TIME(final_t);
    total_t = final_t - inicial_t;

    puts("Análise do tempo:");
    printf("T1: Inicializar as estruturas de dados: \n%lfs\n", total_t);

    GET_TIME(inicial_t);

    if(nthreads == 1){

        tArgs *args = (tArgs*) malloc(sizeof(tArgs));
        args->m1 = m1;
        args->m2 = m2;
        args->mr = mr;
        args->id = nthreads;
        args->nthreads = nthreads;

        mulmat((void *) args);

    }else{

        // Cria cada thread e passa seus respectivos argumentos     
        for (int i = 0; i < nthreads; i++){
            tArgs *args = (tArgs*) malloc(sizeof(tArgs));       
            args->m1 = m1;
            args->m2 = m2;
            args->mr = mr;
            args->id = i;
            args->nthreads = nthreads;
            pthread_create(&tid[i], NULL, mulmat, (void *) args);
        }
    }    
    
    // Espera cada thread terminar para avançar a computação na main
    for (int i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }

    GET_TIME(final_t);
    total_t = final_t - inicial_t;

    printf("T2: Multiplicação: \n%lfs\n", total_t);

    GET_TIME(inicial_t);

    // Libera posições na memória
    free(m1->pos);
    free(m1);
    
    free(m2->pos);
    free(m2);
    
    free(mr->pos);
    free(mr);

    GET_TIME(final_t);
    total_t = final_t - inicial_t;

    printf("T3: Liberação de posições na memória: \n%lfs\n", total_t);    

}