# Photopobre
O projeto aceita uma imagem no formato PPM como entrada e opera sobre ela.
As operações realizadas são:
- Escala de cinza
- Filtro sépia
- Blur
- Rotação
- Inversão de cores
- Cortar imagem

O projeto contém duas pastas com imagens que representam a imagem original e o
esperado de cada operação. Além disseo, existem arquivos de entrada que contém
as opções de entrada para a operação a ser feita.

Formato PPM
------
O formato PPM descreve a imagem em um arquivo de texto,
que pode ser lido por humanos. Ele segue a seguinte especificação:
- A primeira linha possui a palavra P3
- A segunda linha possui o número de colunas (N) e linhas (M)
- A terceira linha possui o número 255
- As próximas linhas descrevem os pixels da image, são no total M linhas,
  onde cada uma possui N pixels descritos. Cada pixel possui 3 inteiros,
  que vão de 0 a 255. (Veja o Anexo 4 para mais informações sobre o pixel)

```
P3
3 2
255
12  34  56  77 12 33  12 12 12
43 200 100  10 20 30  51  5  1
```

O exemplo acima mostra uma imagem com 2 linhas e 3 colunas.
Se você salvar o exemplo em um arquivo de extensão “.ppm”,
esta imagem poderá ser vista no seu computador como uma imagem normal.


Leitura e Escrita de Imagens
------
Para leitura de imagem, pode-se fazer o uso do comando “cat”.
O seu programa deve ser executado da seguinte forma:

```
cat lena.ppm entrada.txt | ./photopobre > saida.ppm
```
Este comando irá inserir na entrada do seu programa a imagem “lena.ppm”
e o que estiver escrito no arquvido de entrada.txt.
Este arquivo de entrada pode ser utilizado para descrever quantas e quais
operações vão ser feitas nesta imagem. Por exemplo:

```
3
3 15
1
7  10 25  100 300
```

Este exemplo descreve que serão feitas 3 operações na imagem:
- A primeira operação é descrita pela linha “3 15”,
  que representa uma operação de blur com o tamanho de 15
- A segunda operação é descrita pela linha “1” ,
  que representa uma operação de escala de cinza
- A terceira operação é descrita pela linha “7  10 25  100 300“,
  que representa uma operação de corte, que se inicia no ponto (10, 25),
 e tem tamanho de 100 por 300


Criação e conversão de imagens
------
Algumas imagens PPM já estão disponíveis junto com esta descrição de projeto.
Se você quiser utilizar novas imagens que não são PPM,
você pode utilizar o commando “convert” para converter de um formato para o
outro.
Por exemplo, se eu quero converter a image foto-familia.png para PPM,
eu uso o comando:
```
convert foto-familia.png -compress none foto-familia.ppm
```

Pixels e cores
------
Pixels são a menor unidade de uma imagem.
Se o tamanho da image for 300 pro 100, isso quer dizer que a imagem tem
300 colunas e 100 linhas, e um total de 30000 pixels (300 x 100).
Cada pixel possui 3 componentes,
o RGB, do inglês Red, Green e Blue (Vermelho, Verde e Azul).
Cada componente varia de 0 a 255, sendo 0 a ausência daquela cor,
e 255 a total presença daquela cor.


Compilar o Photopobre
------
Para compilar no MacOS é necessário criar um arquivo binário para cada arquivo .c:

```
$ gcc -o main -c main.c -Iheaders
$ gcc -o photofilters -c headers/photofilters.c
$ gcc -o calculations -c headers/calculations.c
$ gcc -o inputout -c headers/inputout.c
$ gcc -o photopobre main photofilters calculations inputout
$ cat lena/lena.ppm entrada.txt | ./photopobre > saida.ppm

```

Para gcc no MacOS é necessário rodar este comando para compilar:

```
$ gcc-4.9 -std=c99 -o photopobre headers/* main.c -Iheaders

```
