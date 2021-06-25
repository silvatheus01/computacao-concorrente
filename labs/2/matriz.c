
#include "matriz.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void naive(Matriz *m1, Matriz *m2, Matriz *mr){

    int dim = m1->dim;    

    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                mr->pos[i*dim + j] += m1->pos[i*dim + k] * m2->pos[k*dim + j];          
            }
        }        
    } 
}

void *mulmat(void *arg){

    tArgs *args = (tArgs*) arg;

    int dim = args->m1->dim;
    int nthreads = args->nthreads;
    int id = args->id;
    
    int *m1 = args->m1->pos;
    int *m2 = args->m2->pos;
    int *mr = args->mr->pos;

    for (int i = id; i < dim; i += nthreads){
        for (int j = 0; j < dim; j++){
            for (int k = 0; k < dim; k++){
                mr[i*dim + j] += m1[i*dim + k] * m2[k*dim + j];          
            }
        }        
    }   

    free(args);
}

void fillm(Matriz *matriz, int dim, int valor){
    matriz->pos = (int *) malloc(sizeof(int) * dim * dim);
    matriz->dim = dim;

    if(valor){
        for (int i = 0; i < (dim * dim); i++){
            matriz->pos[i] = valor;
        }
    }
    
}