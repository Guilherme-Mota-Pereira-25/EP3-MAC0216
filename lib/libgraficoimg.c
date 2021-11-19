#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//TODO: mudar funções auxiliares para arquivos .h e .c separados.
//TODO: comentar as funções a seguir.

char *titulo_grafico = NULL;
char *rotulo_x = NULL;
char *rotulo_y = NULL;
char **titulos_linhas = NULL;
int num_linhas, num_colunas, num_paises;

void define_num_linhas(int *linhas) {
    num_linhas = *linhas;
}

void define_num_colunas(int *colunas) {
    num_colunas = *colunas;
}

void define_titulo (char *titulo) {
    titulo_grafico = titulo;
    titulo_grafico = (char*) malloc((strlen(titulo)+1)*sizeof(char)); 
    strcpy(titulo_grafico, titulo);
}

void define_rotulo_x (char *nome) {
    rotulo_x = nome;
    rotulo_x = (char*) malloc((strlen(nome)+1)*sizeof(char)); 
    strcpy(rotulo_x, nome);
}

void define_rotulo_y (char *nome) {
    rotulo_y = nome;
    rotulo_y = (char*) malloc((strlen(nome)+1)*sizeof(char)); 
    strcpy(rotulo_y, nome);
}

void define_nomes_linhas (char *nomes_linhas[]) {
    num_paises = num_linhas-1; // excluindo a linha que contém os anos.
    titulos_linhas = (char**) malloc(num_paises*sizeof(char*));
    for (int i = 0; i < num_paises; i++) {
        int num_caracteres = strlen(nomes_linhas[i]) + 1;
        titulos_linhas[i] = (char*) malloc(num_caracteres*sizeof(char));
        strcpy(titulos_linhas[i],nomes_linhas[i]);
    }   
}

void desaloca_string(char* str) {
    free(str);
    str = NULL;
}

void desaloca_vetor_strings(char** strs, int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        free(strs[i]);
        strs[i] = NULL;
    }
    free(strs);
    strs = NULL;
}

void desenha_grafico (int linhas, int colunas, float planilha[][colunas]) {

    // Primeiramente, vamos montar um arquivo com os dados na formatação cor-
    // reta para poder ser processado pelo gnuplot.
    FILE* dados_formatados = fopen("/tmp/dados.dat", "w");
    
    for (int j = 0; j < num_colunas; j++) {
        for (int i = 0; i < num_linhas; i++) {
            fprintf(dados_formatados,"%f ", planilha[i][j]);
        }
        fprintf(dados_formatados, "\n");
    }

    // Agora vamos montar o arquivo com os comandos do gnuplot a serem executados.
    FILE* especific_gnu = fopen("/tmp/especific_gnu.", "w");

    char* comando_setar_titulo = "set title ";
    strcat(comando_setar_titulo, titulo_grafico);

    char* comando_setar_saida = "set output \"grafico.png\"";

    char* comando_setar_rotulo_x = "set xlabel ";
    strcat(comando_setar_rotulo_x, rotulo_x);
    
    char* comando_setar_rotulo_y = "set ylabel ";
    strcat(comando_setar_rotulo_y, rotulo_y);

    char* comando_plotar = "plot ";

    for (int i = 0; i < num_paises; i++) {
        char* config_pais = "\"dados.dat\" using 1:";

        char coluna[1];
        itoa(i+2,coluna,10); // convertendo i+2 de inteiro para string.
                             // somamos dois, pois contamos a partir da
                             // segunda coluna(1a contém os anos).

        char cor[1];
        itoa(i,cor,10); // convertendo i de inteiro para string.
       
        strcat(config_pais, coluna);
        strcat(config_pais, " title ");
        strcat(config_pais, titulos_linhas[i]);
        strcat(config_pais, " linetype 7 linecolor ");
        strcat(config_pais, cor);
        strcat(config_pais, " with linespoints");

        if (i != num_paises-1) strcat(config_pais, ",");

        strcat(comando_plotar, config_pais);
    }

    char* comandos_gnu[] = { comando_setar_titulo, 
                             comando_setar_saida,
                             comando_setar_rotulo_x,
                             comando_setar_rotulo_y,
                             comando_plotar
                            };
    
    execvp("/usr/bin/gnuplot", comandos_gnu);

    fclose(dados_formatados);
    fclose(especific_gnu);

    // Como já realizamos a tarefa desejada, vamos, agora, desalocar toda a 
    // memória alocada para as variáveis declaradas ao início do arquivo.
    desaloca_string(titulo_grafico);
    desaloca_string(rotulo_x);
    desaloca_string(rotulo_y);
    desaloca_vetor_strings(titulos_linhas, num_paises);
}

