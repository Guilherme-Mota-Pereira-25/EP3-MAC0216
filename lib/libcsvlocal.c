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
    char c = '*';
    int numero_colunas = 0;
    while(c != '\n') {
        fscanf(fp, "%c", &c);
        if(c == ',') numero_colunas++;
    }
    if(numero_colunas > 1000) 
        return -1;
    (*colunas) = numero_colunas;
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
    fp = fopen ("BRICS_MortalidadeInfantil.csv", "r");
    if (fp == NULL) {
        tratamento_erro("Erro ao abrir arquivo", -1, 1);
    }    
    tratamento_erro("Número máximo de colunas excedido. Tente outro arquivo", conta_colunas(fp, colunas), 0);
    
    char c = '*';
    int numero_linhas = 0;
 
    //while(c != '\n') {
        //próxima palavra
        while (c != ',') 
            fscanf(fp, "%c", &c);
        int i;
        for(i = 0; i < *(colunas); i++) {
            fscanf(fp, "%c", &c);
            if(c == ',') {
                planilha[numero_linhas][i] = 0.0;
            } else {
                fseek(fp, -1L, SEEK_CUR);
                fscanf(fp, "%f", &planilha[i][numero_linhas]);
                fseek(fp, 1L, SEEK_CUR);
            }
        }

        //fscanf(fp, "%c", &c);
    //}
    //printf("%f", planilha[0][0]);

    fclose(fp);
}