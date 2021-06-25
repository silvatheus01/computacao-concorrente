#ifndef MATRIZ_H
#define MATRIZ_H

// Definição de uma Matriz
typedef struct _Matriz{    
    int *pos; 
    int dim;
} Matriz;

// Argumentos usados pela tarefa executada pela thread
typedef struct _tArgs{
    Matriz *m1, *m2, *mr;
    int id, nthreads;
} tArgs;

// Capaz de fazer a multiplicação de matrizes concorrentemente 
void *mulmat(void *arg);

// Preenche todas as posições da matriz com a dimensão e valor dados
void fillm(Matriz *matriz, int dim, int valor);

// Algoritmo ingênuo para multiplicação de matrizes
void naive(Matriz *m1, Matriz *m2, Matriz *mr);

#endif




