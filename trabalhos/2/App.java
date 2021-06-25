public class App {
    public static void main(String[] args){

        int nSensores;
        boolean isRegistrador;
        int aux;       

        try{
            nSensores = Integer.parseInt(args[0]);
            aux = Integer.parseInt(args[1]);
        }catch(NumberFormatException e){
            throw new NumberFormatException("Entre com o número de threads e o sinal para registrar ou não.");
        }catch(ArrayIndexOutOfBoundsException e){
            throw new ArrayIndexOutOfBoundsException("Falta argumentos na entrada.");
        }

        if(aux > 0){
            isRegistrador = true;
        }else{
            isRegistrador = false;
        }
             
        Thread sensores[] = new Thread[nSensores];
        Thread atuadores[] = new Thread[nSensores];

        Banco banco = new Banco(isRegistrador);

        for(int i = 0; i < nSensores; i++){
            Sensor sensor = new Sensor(i, banco);
            sensores[i] = sensor;
            atuadores[i] = new Atuador(sensor);

            sensores[i].start();
            atuadores[i].start();
        }
    }
}
