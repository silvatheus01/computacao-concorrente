#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include "integral.h"

double altura(double x){
    // Função que será integrada:
    return log(pow(x,2) + cos(x));
}

void *integra_c(void *arg){
    Args *args = (Args*) arg;
    double n = args->n;
    double linf = args->linf;
    double lsup = args->lsup;
    double base = (lsup - linf)/n;
    int id = args->id;
    int nthreads = args->nthreads;

    double *count = (double*) malloc(sizeof(double));
    *count = 0.0;

    double temp = 0.0;
    double aux = linf + base*id;
    
    for (; aux < lsup; aux += base*nthreads){
        temp += altura(aux)*base;
    }   

    (*count) = temp;    
    pthread_exit(count);

}

double integra_s(double n, double linf, double lsup){
    double count = 0.0;
    double base = (lsup - linf)/n;
    double aux = linf + base;
    
    for (; aux < lsup; aux += base){
        count += altura(aux)*base;
    }   

    return count;
}