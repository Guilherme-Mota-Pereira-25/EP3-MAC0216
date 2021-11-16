/* This file is the implementation of 
 * the csvlocal library.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

int pula_celula(FILE *fp) {
    int fim_arq;
    char c = '*';
    while((fim_arq = fscanf(fp, "%c", &c)) != EOF 
        && c != ',' && c != '\n') {}
    if(fim_arq == EOF) return -1;
    if(c == '\n') return 1;
    return 0;
}

int conta_colunas(FILE *fp, int *colunas) {
    int numero_colunas = 0;
    int fim_arq;
    while((fim_arq = pula_celula(fp)) == 0) numero_colunas++;
    if(numero_colunas > 1000 || numero_colunas <= 0 
        || fim_arq == -1) return -1;
    *colunas = numero_colunas;
    return 0; 
}

int cria_planilha(FILE *fp, float planilha[1000][1000], int *linhas, int colunas) {
    char c = '*';
    int numero_linhas = 0;

    while(pula_celula(fp) != -1) {
        int i;
        int fim_arq;
        for(i = 0; i < colunas; i++) {
            if((fim_arq = fscanf(fp, "%c", &c)) == EOF) break;
            if(c == ',' || c == '\n') planilha[numero_linhas][i] = 0.0;
            else {
                fseek(fp, -1L, SEEK_CUR);
                fscanf(fp, "%f", &planilha[numero_linhas][i]);
                fseek(fp, 1L, SEEK_CUR);
            }
        }
        if(fim_arq == EOF) return -1;
        numero_linhas++;
    }

    if(numero_linhas > 1000 || numero_linhas <= 0) return -1;
    *linhas = numero_linhas;
    
    return 0;
}

//apenas para fins de teste
void imprime_planilha(float planilha[1000][1000], int colunas, int linhas) {
    int i;
    int j;
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            printf("%.1f,", planilha[i][j]);
        }
        printf("\n");
    }
}

void tratamento_erro(char *mensagem, int codigo, int erro_so) {
    if(codigo == -1) {
        if(erro_so)
            perror(mensagem);
        else {
            fprintf(stderr, "%s\n", mensagem);
        }
        exit(EXIT_FAILURE);
    }
}

void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000]) {
    FILE *fp;
    fp = fopen ("./csvtests/BRICS_MortalidadeInfantil.csv", "r");
    if (fp == NULL) {
        tratamento_erro("Erro ao abrir arquivo", -1, 1);
    }    
    tratamento_erro("Erro ao criar a planilha. Formato inválido.", conta_colunas(fp, colunas), 0);
    tratamento_erro("Erro ao criar a planilha. Formato inválido.", cria_planilha(fp, planilha, linhas, *colunas), 0);

    //debug
    //printf("%d", *colunas);
    //printf("%d", *linhas);
    //imprime_planilha(planilha, *colunas, *linhas);
    fclose(fp);
}