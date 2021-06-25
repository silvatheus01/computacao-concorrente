public class Teste {

    public static void main(String[] args){
    
        Banco banco = new Banco(false);

        Sensor sensor = new Sensor(0, banco);
        Atuador atuador = new Atuador(sensor);

        // Esta primeira temperatura não pode ser gravada pois não é maior do que 30
        sensor.gravaTemperatura(30);

        assert(Math.abs(0 - atuador.getTemperaturaMedia()) == 0):
        "Apenas temperaturas acima de 30°C devem ser gravadas no Banco";

        // A Media calculada pelo Atuador correspondente deve ser aproximadamente: 35.66°C.
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(36);

        // Não deve fazer parte do calculo da Media do atuador, pois o sensor é diferente.
        sensor = new Sensor(1, banco);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(32);

        assert(Math.abs(35.66 - atuador.getTemperaturaMedia()) < 0.01):
        "Cada atuador calcula a temperatura media do seu sensor correspondente";

        assert(sensor.getIdLeitura() == 2):
        "Cada sensor deve incrementar em 1 seu idLeitura quando fizer uma gravacao";

        sensor = new Sensor(2, banco);
        atuador = new Atuador(sensor);

        sensor.gravaTemperatura(20);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
       
        assert(Alerta.VERMELHO == atuador.processa()):
        "Se as 5 ultimas gravaçoes do sensor correspondente forem maiores que 35°C, o atuador deve gerar um Alerta Vermelho.";

        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(40);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(33);
        sensor.gravaTemperatura(39);
        sensor.gravaTemperatura(37);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);

        assert(Alerta.AMARELO == atuador.processa()):
        "Se entre as 15 ultimas gravaçoes do sensor correspondente, 5 forem maiores que 35°C, o atuador deve gerar um Alerta Amarelo.";

        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(33);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(33);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(33);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(33);
        sensor.gravaTemperatura(31);
        sensor.gravaTemperatura(31);

        assert(Alerta.NORMAL == atuador.processa()):
        "O atuador deve gerar um Alerta de condiçoes normais caso nenhum outro alerta seja gerado";  
    }
}
