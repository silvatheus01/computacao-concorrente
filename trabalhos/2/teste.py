class Teste:
    def __init__(self):
        # Numero de sensores esperando para gravar
        self.n_sensores_esperando = 0
        # Numero de atuadores esperando para processar
        self.n_atuadores_esperando = 0

        # Numero de sensores gravando
        self.n_sensores_gravando = 0
        # Numero de atuadores processando
        self.n_atuadores_processando = 0

        # Linha atual do programa python. Começa a contar a partir do primeiro método executado.
        self.count_linhas = 3

    "Método sinaliza que um Sensor começou a gravar."
    def gravando(self):
        if self.n_sensores_gravando > 0:
            print('Linha ' + str(self.count_linhas) + ': SOLUÇÃO INCORRETA: Sensores gravando simultaneamente.')
        if self.n_atuadores_processando > 0:
            print('Linha ' + str(self.count_linhas) + ': SOLUÇÃO INCORRETA: Sensor gravando com atuadores processando.')

        self.n_sensores_gravando += 1
        self.n_sensores_esperando -= 1

        self.count_linhas += 1
    
    "Método sinaliza que um Atuador começou a processar."
    def processando(self):
        if self.n_sensores_esperando > 0:
            print('Linha ' + str(self.count_linhas) + ': SOLUÇÃO INCORRETA: Atuador começou a processar com sensores esperando.')
        if self.n_sensores_gravando > 0:
            print('Linha ' + str(self.count_linhas) + ': SOLUÇÃO INCORRETA: Atuador processando com sensores gravando. ')

        self.n_atuadores_processando += 1
        self.n_atuadores_esperando -= 1
        
        self.count_linhas += 1
    

    "Método sinaliza que um Sensor deseja gravar."
    def deseja_gravar(self):
        self.n_sensores_esperando += 1
        self.count_linhas += 1

    "Método sinaliza que um Atuador deseja gravar."
    def deseja_processar(self):
        self.n_atuadores_esperando += 1
        self.count_linhas += 1
    
    "Método sinaliza que um Sensor gravou."
    def gravou(self):
        self.n_sensores_gravando -= 1    
        self.count_linhas += 1  
    
    "Método sinaliza que um Atuador processou."
    def processou(self):        
        self.n_atuadores_processando -= 1
        self.count_linhas += 1

