/* This file contains the main function
 * that will execute the four libraries
 * created.
*/

#include <stdio.h>
#include "libcsvreader.h"

int main() {
    float **planilha;
    char *caminho_dos_dados;
    int *linhas;
    int *colunas;

    carrega_dados(caminho_dos_dados, linhas, colunas, planilha);
    return 0;
}