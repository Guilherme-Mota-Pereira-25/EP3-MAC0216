/* This file contains the main function
 * that will execute the four libraries
 * created.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/libcsvreader.h"
#include "../include/libgraficos.h"

int main(int argc, char *argv[]) {

    char *caminho_dos_dados = argv[1];
    char *titulo_do_grafico = argv[2];
    char *rotulo_eixo_x = argv[3];
    char *rotulo_eixo_y = argv[4];
    char *nomes_linhas[1000];
    
    float planilha[1000][1000];
    int *linhas = NULL;
    int *colunas = NULL;

    carrega_dados(caminho_dos_dados, linhas, colunas, planilha, nomes_linhas);

    define_num_linhas(linhas);
    define_num_colunas(colunas);
    define_titulo(caminho_dos_dados);
    define_rotulo_x(rotulo_eixo_x);
    define_rotulo_y(rotulo_eixo_y);
    define_nomes_linhas(nomes_linhas);
    desenha_grafico(*linhas, *colunas, planilha);

    // TODO: desalocar memória das variáveis utilizadas.

    return 0;
}