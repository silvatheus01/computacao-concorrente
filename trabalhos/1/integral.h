#ifndef MATRIZ_H
#define MATRIZ_H

// Argumentos passados para as threads
typedef struct _Args{    
    double lsup, linf, n;
    int id, nthreads;
} Args;

// Calcula a integral da função matemática em altura() concorrentemente
void *integra_c(void *arg);

// Calcula a integral da função matemática em altura() sequencialmente
double integra_s(double n, double linf, double lsup);

// Retorna f(x) 
double altura(double x);

#endif
