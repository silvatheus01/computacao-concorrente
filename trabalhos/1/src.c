#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "timer.h"
#include "integral.h"

int main(int argc, char **argv){    

    double ini, fim, tseq, tpar;    
    double speedup;

    GET_TIME(ini);

    if(argc < 5){
        puts("Falta argumentos na entrada.");
        return -1;
    }

    double n = strtod(argv[1], NULL);
    double linf = strtod(argv[2], NULL);
    double lsup = strtod(argv[3], NULL);
    int nthreads = strtol(argv[4], NULL, 10);
    double base = (lsup-linf)/n;

    if(nthreads > n){
        nthreads = n;
    }

    GET_TIME(fim);

    tseq += fim - ini;

    GET_TIME(ini);

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

    printf("Resultado da integral: %.20f\n", res);

    GET_TIME(fim);

    tpar += fim - ini;

    printf("Tempo concorrente: %fs\n", tpar + tseq); 

    GET_TIME(ini);

    res = integra_s(n, linf, lsup);
    printf("Resultado da integral: %.20f\n", res);

    GET_TIME(fim);

    tseq += fim - ini;
    double aux = fim - ini;

    printf("Tempo sequencial: %fs\n", aux );
    printf("\n");
   
    printf("Speedup teórico utilizando %d thread(s): %f\n",nthreads ,tseq/((aux/nthreads) + (tseq - aux)));
    printf("Speedup real: %f\n", tseq/((tseq - aux) + tpar));

    pthread_exit(NULL);
    
    
}