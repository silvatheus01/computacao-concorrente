import java.util.concurrent.ThreadLocalRandom;

public class Sensor extends Thread{

    private final long TEMPO = 1000;

    /** ID do Sensor. */
    private int index;

    private Banco banco;

    /** ID de leitura do Sensor. */
    private int idLeitura = 0;

    Sensor(int index, Banco banco){
        this.banco = banco;
        this.index = index;
    }

    public Banco getBanco(){
        return this.banco;
    }

    public int getIndex(){
        return this.index;
    }

    public int getIdLeitura(){
        return this.idLeitura;
    }

    /** Método grava um temperatura no banco.
     *
     * @param temperatura - Temperatura que será gravada.
     * @return boolean - Retorna true se a gravação foi feita.
    */
    public boolean gravaTemperatura(int temperatura){
        if(temperatura > 30){
            Dado dado = new Dado(temperatura, this.index, this.idLeitura);
            banco.putDado(dado); 
            this.idLeitura++; 
            return true;
        }              
        return false;
    }    

    public void run(){

        int temperatura;

        while(true){
            try{
                sleep(this.TEMPO);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            temperatura = ThreadLocalRandom.current().nextInt(25,41);

            System.out.printf("Sensor %d: Deseja gravar a temperatura %d°C.\n", this.index, temperatura);
            if(gravaTemperatura(temperatura)){
                System.out.printf("Sensor %d: Gravou a temperatura %d°C.\n", this.index, temperatura);
            }else{
                System.out.printf("Sensor %d: Temperatura <= 30°C. Gravação não realizada!\n", this.index);
            }  
        }       
    }
    
}
