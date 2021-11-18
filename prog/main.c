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
    float **planilha;
    int *linhas;
    int *colunas;

    carrega_dados(caminho_dos_dados, linhas, colunas, planilha);

    define_num_linhas(linhas);
    define_num_colunas(colunas);

    define_titulo(caminho_dos_dados);
    define_rotulo_x("Ano");

    // TODO: pegar o rótulo do eixo y a partir do caminho dos dados, visto que
    // há um padrão no nome dos arquivos.
    define_rotulo_y("");

    // TODO: usar vetor com os titulos das linhas, guardado na biblioteca dinâmica.
    // define_nomes_linhas();
    
    // TODO: terminar a função desenha_grafico.
    // desenha_grafico();

    // TODO: desalocar memória das variáveis utilizadas.

    return 0;
}