#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int *vet, nthreads, flag, salto;
pthread_mutex_t lock;
pthread_cond_t cond;

void *soma(void *arg){
    int *id = (int *) arg;
    int aux;

    pthread_mutex_lock(&lock);
    while(*id >= salto){
       
        aux = vet[(*id)-salto];
        flag++;
        if(flag == (nthreads - salto)){
            flag = 0; 
            pthread_cond_broadcast(&cond);
            
        }else{            
            pthread_cond_wait(&cond, &lock);                       
        }
        
        vet[*id] = vet[*id] + aux;
        flag++;
        
        if(flag == (nthreads - salto)){                        
            flag = 0;
            salto = salto*2;
            pthread_cond_broadcast(&cond);
        }else{  
            pthread_cond_wait(&cond, &lock);          
        }             
          
    }
    pthread_mutex_unlock(&lock); 

    pthread_exit(NULL);
    
    
}

void printv(int *vetor, int nthreads){
    for (int i = 0; i < nthreads; i++){
        printf("%d ", vetor[i]);
    }

    printf("\n");
    
}

int main(int argc, char **argv){
    if(argc < 2){
        puts("Falta argumentos na entrada!");
        return -1;
    }

    int n = strtol(argv[1], NULL, 10);
    nthreads = pow(2,n);

    vet = (int*) malloc(sizeof(int)*nthreads);
    int *vtest = (int*) malloc(sizeof(int)*nthreads);

    flag = 0;
    salto = 1;

    for (int i = 0; i < nthreads; i++){
        vet[i] = i;
        vtest[i] = i;
    }

    printv(vet, nthreads);    

    for (int i = 0; i < nthreads; i++){
        vtest[i] = vtest[i] + vtest[i-1];
    }
    
    pthread_t tid[nthreads];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);


    for (int i = 0; i < nthreads; i++){
        int *id = (int*) malloc(sizeof(int));
        *id = i;
        if(pthread_create(&tid[i], NULL, soma, (void*) id)){
            puts("Erro em pthread_create()");
            return -2;
        }
    }

    for (int i = 0; i < nthreads; i++){
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < nthreads; i++){
        if(vet[i] != vtest[i]){
            puts("Soma calculada erradamente.");
            return -3;
        }
    }

    printv(vet, nthreads);

    puts("Soma calculada corretamente.");

    free(vet);
    free(vtest);
    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);

}