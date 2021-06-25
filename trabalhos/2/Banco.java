import java.util.ArrayList;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedWriter;

public class Banco {
    /** Posição da última gravação feita no banco.*/
    private int pos = -1;

    final private int DIMENSAO = 60;
    final private int AMOSTRA = 15;
    
    /** Quantidade de atuadores processando.*/
    private int countAtuadores = 0;

    /** Quantidade de sensores que desejam escrever.*/
    private int querEscrever = 0;

    /** Indica que um sensor esta escrevendo. Se false, não há nenhum sensor escrevendo.*/
    private boolean escrevendo = false;

    /** Se true, o Banco deve registrar o log completo da aplicação.*/
    private boolean isRegistrador;

    /** Sinaliza ao método geraLog que um novo script python deve ser criado antes de algo ser escrito neste.*/
    private boolean primeiroLog = true;

    /** Lista que guarda os dados da aplicação.*/
    private Dado[] dados = new Dado[DIMENSAO]; 

    public Banco(boolean isRegistrador){
        this.isRegistrador = isRegistrador;
    }

    /** Método para gerar um log da aplicação.
     * @param log - Ação de uma thread.
    */
    private synchronized void geraLog(String log){
        if(this.isRegistrador == true){
            try{

                FileWriter fw;
                BufferedWriter bw;

                if(this.primeiroLog == true){

                    fw = new FileWriter("log.py", false);
                    bw = new BufferedWriter(fw);
                    bw.write("from teste import Teste");
                    bw.newLine();
                    bw.write("t = Teste()");
                    bw.flush();
                    bw.close();

                    this.primeiroLog = false;

                }else{
                    fw = new FileWriter("log.py", true);
                    bw = new BufferedWriter(fw);
                    bw.newLine();
                    bw.write(log);
                    bw.flush();
                    bw.close();
                }                
    
            }catch(IOException e){
                e.printStackTrace();
            }
        }   
    }

    /** Método determina se um Atuador pode processar.*/
    private synchronized void entraAtuador(){

        geraLog("t.deseja_processar()");

        try{
            while(this.querEscrever > 0 || this.escrevendo == true || this.pos == -1){ 
                wait();
            }

        }catch(InterruptedException e){
            e.printStackTrace();
        }

        this.countAtuadores++;

        geraLog("t.processando()");  
        
    }

    /** Método sinaliza que um Atuador parou de processar.*/
    private synchronized void saiAtuador(){
        
        this.countAtuadores--; 
        if(this.countAtuadores == 0){
            notify();
        } 
        
        geraLog("t.processou()");
    }

    /** Método determina se um Sensor pode gravar.*/
    private synchronized void entraSensor(){

        geraLog("t.deseja_gravar()");

        this.querEscrever++;

        while(this.countAtuadores > 0 || this.escrevendo == true){
            try{             
                wait();
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }
       
        this.querEscrever--;
        this.escrevendo = true;

        geraLog("t.gravando()");
    }
    
    /** Método sinaliza que um Sensor parou de gravar.*/
    private synchronized void saiSensor(){     
        
        this.escrevendo = false;
        notifyAll();  
        
        geraLog("t.gravou()");
    }

    /** Método que insere um Dado no banco.
     * 
     * @param dado - Dado que será inserido.
    */
    public void putDado(Dado dado){

       this.entraSensor();
               
        this.pos = (this.pos + 1) % this.DIMENSAO;
        this.dados[this.pos] = dado;      

        this.saiSensor();

    }

    /** Método retorna, se possível, as 15 últimas temperaturas gravadas no banco por um certo Sensor.
     * 
     * @param sensor - Sensor que fez as gravações.
     * @return ArrayList<Dado> - Um ArrayList que contém as temperaturas computadas.
    */
    public ArrayList<Dado> getDados(Sensor sensor){     

       this.entraAtuador();

       ArrayList<Dado> lista = new ArrayList<Dado>();
   
        int i = this.pos;
        int flag = 0;
        for(int j = 0; j < this.DIMENSAO; j++){

            if(this.dados[i] != null){
                
                if(this.dados[i].getIdSensor() == sensor.getIndex()){
                    Dado dado = new Dado(dados[i].getTemperatura(), 
                    dados[i].getIdSensor(),
                    dados[i].getIdLeitura());                   

                    lista.add(dado);                 
                    flag++;

                    if(flag == this.AMOSTRA){
                        break;
                    }
                }              
            
                i--;
                if(i == -1){
                    i = this.DIMENSAO - 1;
                } 

            }else{
                break;
            }                       
        }
        
        this.saiAtuador();           

        return lista;
    }
    
    /** Método calcula a média aritmética das temperaturas existentes no banco gravadas por um certo Sensor. 
     * 
     * @param sensor - Sensor que gravou as temperetaturas no banco.
     * @return float - Média aritmética das temperaturas
    */
    public synchronized float calculaTemperaturaMedia(Sensor sensor){
        float count = 0.0f;
        float valores = 0.0f;

        for(Dado dado : this.dados){
            if(dado != null){
                if(dado.getIdSensor() == sensor.getIndex()){
                    count++;
                    valores += dado.getTemperatura();
                }                
            }else{
                break;
            }            
        }

        if(count == 0.0f){
            return 0.0f;
        }else{
            return valores / count;
        }        
    }
}
