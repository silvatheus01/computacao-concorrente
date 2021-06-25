## Compilando a aplicação

```console
user@pc:~/$ javac App.java
```

## Rodando a aplicação

```console
user@pc:~/$ java App <nthreads> <isRegistrador>
```

Onde `isRegistrador` indica se o banco deve gerar um log ou não. Caso o valor passado seja não negativo, o log será gerado.

## Compilando os testes

```console
user@pc:~/$ javac Teste.java
```

## Rodando os testes

```console
user@pc:~/$ java -ea Teste
user@pc:~/$ python3 log.py
```
Antes de executar o último comando acima, tenha certeza que a aplicação já gerou um log.
