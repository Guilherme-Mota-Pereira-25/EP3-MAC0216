/* Esse arquivo é a implementação da
 * biblioteca csv local 
*/

#include <stdio.h>
#include <stdlib.h>
#include "libcsv.h"

void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000], char *nomes_linhas[1000]) {
    FILE *fp;
    fp = fopen (caminho_dos_dados, "r");
    if (fp == NULL) {
        tratamento_erro(-1, "Erro ao abrir arquivo", 1);
    }    
    tratamento_erro(conta_colunas(fp, colunas, planilha), "Erro ao criar a planilha. Formato inválido.", 0);
    tratamento_erro(cria_planilha(fp, planilha, linhas, *colunas, nomes_linhas), "Erro ao criar a planilha. Formato inválido.", 0);

    //debug
    /*printf("colunas: %d", *colunas);
    printf(" linhas: %d\n", *linhas);
    imprime_planilha(planilha, *colunas, *linhas);
    imprime_nomes(nomes_linhas, *linhas);*/
    fclose(fp);
}