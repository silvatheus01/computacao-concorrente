#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include "integral.h"

#define COR_VERDE "\x1B[32m"
#define RESET_COR "\x1B[0m"
#define COR_VERMELHA "\x1B[31m"

int main(int argc, char **argv){

    if(argc < 5){
        puts("Falta argumentos na entrada.");
        return -1;
    }

    double n = strtod(argv[1], NULL);
    double linf = strtod(argv[2], NULL);
    double lsup = strtod(argv[3], NULL);
    int nthreads = strtol(argv[4], NULL, 10);
    double base = (lsup-linf)/n;

    pthread_t tid[nthreads]; 

    for (int i = 0; i < nthreads; i++){
        Args *args = (Args*) malloc(sizeof(Args));
        args->n = n;
        args->linf = linf;
        args->lsup = lsup;
        args->id = i + 1;
        args->nthreads = nthreads;
        pthread_create(&tid[i], NULL, integra_c, (void*) args);
    }

    double *ret = (double*) malloc(sizeof(double));
    *ret = 0;
    double res = 0;

    for (int i = 0; i < nthreads; i++){
        pthread_join(tid[i], (void**) &ret);
        res += *ret;
    }

    double limite = 0.1;
    double integral =  integra_s(n, linf, lsup);
    double erro = res - integral;

    printf("Erro = ");
    if(fabs(erro) > limite){
        printf(COR_VERMELHA "%.20f\n" RESET_COR, erro);
    }else{
        printf(COR_VERDE "%.20f\n" RESET_COR, erro);
    }    

    pthread_exit(NULL);
    
}