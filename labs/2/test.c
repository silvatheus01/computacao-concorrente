#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matriz.h"

#define COR_VERDE "\x1B[32m"
#define RESET_COR "\x1B[0m"
#define COR_VERMELHA "\x1B[31m"

#define VDEFAULT 2

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

    pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);

    Matriz *m1, *m2, *mr1, *mr2;

    m1 = (Matriz *) malloc(sizeof(Matriz));
    m2 = (Matriz *) malloc(sizeof(Matriz));
    mr1 = (Matriz *) malloc(sizeof(Matriz));
    mr2 = (Matriz *) malloc(sizeof(Matriz));

    fillm(m1, dim, VDEFAULT);
    fillm(m2, dim, VDEFAULT);
    fillm(mr1, dim, 0);
    fillm(mr2, dim, 0);

    if(nthreads == 1){

        tArgs *args = (tArgs*) malloc(sizeof(tArgs));
        args->m1 = m1;
        args->m2 = m2;
        args->mr = mr1;
        args->id = nthreads;
        args->nthreads = nthreads;

        mulmat((void *) args);

    }else{

        // Cria cada thread e passa para esta seus respectivos argumentos     
        for (int i = 0; i < nthreads; i++){
            tArgs *args = (tArgs*) malloc(sizeof(tArgs));       
            args->m1 = m1;
            args->m2 = m2;
            args->mr = mr1;
            args->id = i;
            args->nthreads = nthreads;
            pthread_create(&tid[i], NULL, mulmat, (void *) args);
        }
    }

    naive(m1, m2, mr2);

    for (int i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }    

    for (int i = 0; i < (dim*dim); i++)
    {
        if(mr1->pos[i] != mr2->pos[i]){
            puts(COR_VERMELHA "Algoritmo de Multiplicação implementado incorretamente!" RESET_COR);
            exit(-1);
        }            

    }

    puts(COR_VERDE "Algoritmo de Multiplicação implementado corretamente!" RESET_COR);

    free(m1->pos);
    free(m1);
    
    free(m2->pos);
    free(m2);
    
    free(mr1->pos);
    free(mr1);

    free(mr2->pos);
    free(mr2);

}