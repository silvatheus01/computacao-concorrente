public class Dado {
    private int idSensor;
    private int idLeitura;
    private int temperatura;

    Dado(int temperatura, int idSensor, int idLeitura){
        this.temperatura = temperatura;
        this.idSensor = idSensor;
        this.idLeitura = idLeitura;
    }

    public int getTemperatura(){
        return this.temperatura;
    }

    public int getIdSensor(){
        return this.idSensor;
    }

    public int getIdLeitura(){
        return this.idLeitura;
    }
}
