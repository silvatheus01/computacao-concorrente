#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

long long int n;
int nthreads;

double pi_s(long long int n){
    double soma;
    for (int i = 0; i < n; i++){
        soma += pow(-1, i)/(2*i + 1);
    }
    soma = 4*soma;

    return soma;
}

void *pi_c(void* arg){

    int *id = (int*) arg;
    double *soma = (double *) malloc(sizeof(double));
    *soma = 0;

    int lim;

    if(*id == nthreads-1) lim = n;
    else lim = ((*id)+1)*(n/nthreads);

    for (int i = (*id)*(n/nthreads); i < lim; i++){
        *soma += pow(-1, i)/(2*i + 1);
    }
    *soma = 4*(*soma);
    
    pthread_exit(soma);
}

int main(int argc, char **argv){
    if(argc < 3){
        printf("Entre com: %s <N> <T>\n ", argv[0]);
        exit(-1);
    }

    n = strtoll(argv[1], NULL, 10);
    nthreads = strtol(argv[2], NULL, 10);
    double soma_c, soma_s;

    double ini_t, fim_t, cdelta_t, sdelta_t;
    GET_TIME(ini_t);

    pthread_t *tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);

    if(tid == NULL){
        puts("Erro em malloc. Abortando...");
    }

    int *id = (int *) malloc(sizeof(int)*nthreads);

    for (int i = 0; i < nthreads; i++){
        id[i] = i;
        if(pthread_create(&tid[i], NULL, pi_c, (void*) &id[i])){
            puts("Erro em pthread_create. Abortando...");
            exit(-1);
        }
    }

    double *ret = (double *) malloc(sizeof(double));

    if(ret == NULL){
        puts("Erro em malloc. Abortando...");
    }  

    for (int i = 0; i < nthreads; i++){
        if(pthread_join(tid[i], (void**) &ret)){
           puts("Erro em pthread_join. Abortando...");
           exit(-1);
       }

       soma_c += *ret;
    }

    GET_TIME(fim_t);
    cdelta_t = fim_t - ini_t;

    GET_TIME(ini_t);
    soma_s = pi_s(n);
    GET_TIME(fim_t);
    sdelta_t = fim_t - ini_t;
       
    printf("%.15lf - Concorrente: %lfs\n", soma_c, cdelta_t);
    printf("%.15lf - Sequencial: %lfs\n", soma_s, sdelta_t);
    printf("%.15lf - Constante de math.h\n", M_PI);

    free(ret);
    free(tid);
    free(id);
    
}