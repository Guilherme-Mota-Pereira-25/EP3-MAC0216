/* This file contains the main function
 * that will execute the four libraries
 * created.
*/

#include <stdio.h>
#include "libcsvreader.h"

int main(int argc, char *argv[]) {
    float planilha[1000][1000];
    char *caminho_dos_dados = argv[1];
    int linhas;
    int colunas;

    carrega_dados(caminho_dos_dados, &linhas, &colunas, planilha);
    return 0;
}