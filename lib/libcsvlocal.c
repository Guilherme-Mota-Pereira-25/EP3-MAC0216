/* This file is the implementation of 
 * the csvlocal library.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

int conta_linhas(FILE *fp, int *linhas) {
    return 0;
}

int conta_colunas(FILE *fp, int *colunas) {
    return 0;
}

int cria_planilha(FILE *fp, float planilha[1000][1000]) {
    return 0;
}

void tratamento_erro(char *mensagem, int codigo, int erro_so) {
    if(codigo == -1) {
        if(erro_so)
            perror(mensagem);
        else {
            fprintf(stderr, "%s\n", mensagem);
        }
        exit(1);
    }
}

void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000]) {

    FILE *fp;
    fp = fopen ("unexist.txt", "rb");
    if (fp == NULL) {
        tratamento_erro("Erro ao abrir arquivo", -1, 1);
    }    

    tratamento_erro("Número de colunas inválido. Tente outro arquivo", conta_colunas(fp, colunas), 0);
    tratamento_erro("Número de linhas inválido. Tente outro arquivo", conta_linhas(fp, linhas), 0);
    tratamento_erro("Erro ao ler dados da planilha. Tente outro arquivo", cria_planilha(fp, planilha), 0);

    fclose(fp);
}