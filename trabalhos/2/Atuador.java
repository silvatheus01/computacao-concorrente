import java.util.ArrayList;

public class Atuador extends Thread{

    private final int TEMPO = 2000;
    private final int TEMPERATURA_PERIGOSA = 35;
    private Sensor sensor;

    Atuador(Sensor sensor){
       this.sensor = sensor;
    }

    /** Método processa as temperaturas e retorna um Alerta.
     * 
     * @return Alerta - Alerta computado.
    */
    public Alerta processa(){

        int tempVermelha = 0;
        int tempAmarela = 0;

        ArrayList<Dado> lista = this.sensor.getBanco().getDados(this.sensor);    
        
        for (Dado dado : lista) {
            if(dado.getTemperatura() > this.TEMPERATURA_PERIGOSA){                   
                tempAmarela++;                
            }
        }

        for(int i = 0; i < lista.size(); i++){
            if(lista.get(i).getTemperatura() > this.TEMPERATURA_PERIGOSA){
                tempVermelha++;
            }
            if(i == 4){
                break;
            }
        } 

        if(tempVermelha == 5){
            return Alerta.VERMELHO;
        }else if(tempAmarela >= 5){
            return Alerta.AMARELO;
        }else{
            return Alerta.NORMAL;
        }
    }

    /** Método retorna a média aritmética das temperaturas existentes no banco gravadas pelo Sensor correspondente.
     * 
     * @return float - Média aritmética das temperaturas.
    */
    public float getTemperaturaMedia(){
        return this.sensor.getBanco().calculaTemperaturaMedia(this.sensor);
    }

    public void run(){  

        while(true){
            try{
                sleep(this.TEMPO);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.printf("Atuador %d: Deseja processar.\n", this.sensor.getIndex());
            Alerta alerta = processa();
            System.out.printf("Atuador %d: Processou.\n", this.sensor.getIndex());

            if(alerta == Alerta.VERMELHO){
                System.out.printf("Atuador %d: Alerta vermelho!\n", this.sensor.getIndex());
            }else if(alerta == Alerta.AMARELO){
                System.out.printf("Atuador %d: Alerta amarelo!\n", this.sensor.getIndex());
            }else{
                System.out.printf("Atuador %d: Condições normais de temperatura.\n", this.sensor.getIndex());
            }

            System.out.printf("Atuador %d: Temperatura media do sensor: %.2f°C\n", this.sensor.getIndex(), getTemperaturaMedia());

        }
    }
}
