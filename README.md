Repositório cujo fim é facilitar o progresso do desenvolvimento do 3º Exercício Programa da disciplina MAC0216/DCC/IME/USP.

A diretório "include" contém as interfaces das bibliotecas O diretório "lib" contém os .c, os .o e os .so das bibliotecas O diretório "prog" contém o main.c e os executáveis que vem dele.

## Compilação

Para compilar e criar os executáveis, rodar:

`export LD_LIBRARY_PATH=./lib 

`make`

A compilação irá gerar 6 executáveis no diretório prog. São dois tipos para cada tipo de sáida de gráfico: um local que recebe o caminho para um arquivo csv salvo localmente e uma externa que  recebe uma url de um arquivo csv.

- Gráficos no terminal: main_ext_ascii e main_local_ascii

- Gráficos em png: main_ext_img e main_local_img

- Gráficos em janela: main_ext_extra e main_local_extra

## Excução

Para execução das bibliotecas locais:

`./main_local_png -caminho_csv -titulo_grafico -rotulo_x -rotulo_y`

Para execução das bibliotecas externas:

`./main_ext_png -url_csv -titulo_grafico -rotulo_x -rotulo_y`

### Exemplo
`./main_ext_png http://www.ime.usp.br/~kon/tmp/BRICS_MortalidadeInfantil.csv "Mortalidade Infantil" "Ano" "Mortalidade"`