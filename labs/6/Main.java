class Incrementador extends Thread{

    private int id;
    private int nthreads;
    private int[] vetor;

    Incrementador(int id, int nthreads, int[] vetor){
        this.id = id;
        this.nthreads = nthreads;
        this.vetor = vetor;
    }
    
    public void run(){
        for(int i = id; i < this.vetor.length; i += this.nthreads) {
            this.vetor[i]++;
        }
    }


}

class Main {
    
    public static void main(String[] args){

        int n = Integer.parseInt(args[0]);
        int nthreads = Integer.parseInt(args[1]);
        Thread threads[] = new Thread[nthreads];

        if(nthreads > n){
            nthreads = n;
        }

        int[] vetor = new int[n];

        for(int i = 0; i < vetor.length; i++){
            vetor[i] = i;
            System.out.print(vetor[i] + " ");
        }

        System.out.print("\n");

        for(int i = 0; i < nthreads; i++){
            threads[i] = new Incrementador(i, nthreads, vetor);
            threads[i].start();
        }

        //espera pelo termino de todas as threads
        for (int i = 0; i < threads.length; i++) {
            try { 
                threads[i].join(); 
            } catch (InterruptedException e){ 
                return; 
            }
        }

        for(int i = 0; i < vetor.length; i++){
            System.out.print(vetor[i] + " ");
        }

        System.out.print("\n");


    }
}
