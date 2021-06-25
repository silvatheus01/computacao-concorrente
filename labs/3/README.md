# Cálculo de π usando Concorrência
Foram usadas a [Fórmula de Leibniz para π](https://pt.wikipedia.org/wiki/F%C3%B3rmula_de_Leibniz_para_%CF%80) e a biblioteca `pthread.h` para este cálculo.

## Compilando
```console
user@pc:~/$ gcc src.c -o src -Wall -lm -lpthread
```
## Rodando
Para rodar o programa utilize o seguinte padrão:
```console
user@pc:~/$ ./src 1000 2
```
Onde "1000" é igual a *n* no cálculo da série e "2" é o número de *threads* utilizadas na computação.

## Testando Corretude
Para testar a acurácia do cálculo, foram utilizados um algoritmo sequencial e um concorrente na computação da série. Na saída padrão, é possível ver os valores de π calculados em cada algoritmo e o tempo requisitado em cada um destes, além da constante *M_PI* da biblioteca `math.h` para testar a corretudo do problema. A saída é parecida com essa:

```console
user@pc:~/$ ./src 100000000 2
3.141592643590251 - Concorrente: 1.890081s
3.141592643589326 - Sequencial: 3.180720s
3.141592653589793 - Constante de math.h
```
Caso o valor de *n* aumente, o erro numérico diminui.

É possível notar que os resultados dos algoritmos sequencial e concorrente **não são iguais**. Isso ocorreu porque o computador não consegue representar com exatidão os números em ponto flutuante a partir de certa casa decimal, ocasionando assim arredondamentos. Como a soma da série é diferente em cada algoritmo, esse "erro" é mais perceptível.

Dessa forma, não é possível aferir qual resultado se aproxima mais rapidamente do valor exato de π, pois como foi dito, ambos são bem parecidos. Contudo, é possível dizer que, em termos numéricos, a abordagem concorrente se aproxima mais rapidamente do valor de π.

## Ganho de Desempenho

Para a visualização do ganho de desempenho, foi necessário entrar com um valor para _n_ da ordem de `10e+8`. Para ordens menores, não foi possível ver maiores diferenças. As tabelas a seguir mostram alguns dados importantes sobre o tempo requisitado para cada entrada:

| n        |Valor de π|Tempo Sequencial|
| -------- |----------|-----|
| 10       |3.041839618929403|0.000001s|
| 1000      |3.140592653839794|0.000031s|
| 100000000 |3.141592643589326|3.249482s|

| n        | threads     |Valor de π|Tempo Concorrente|
| -------- |-------------|----------|-----|
| 10       | 2 |3.041839618929403|0.000681s|
| 1000      | 2      |3.140592653839795|0.000376s|
| 100000000 | 2      |3.141592643590251|1.828807s|

Como é possível ver, a abordagem concorrente apenas é interessante, do ponto de vista do ganho de desempenho, a partir de valores de _n_ de ordem alta, como foi expresso. Isso é provado pois para _n = 100000000_, o algoritmo concorrente, utilizando duas threads, computa a série em 1.828807s, enquanto o sequencial calcula em 3.249482s.
