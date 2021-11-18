#include "../include/libgraficos.h"

//TODO: comentar as funções a seguir.

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
    titulos_linhas = (char**) malloc(num_linhas*sizeof(char*));
    for (int i = 0; i < num_linhas; i++) {
        int num_caracteres = strlen(nomes_linhas[i]) + 1;
        titulos_linhas[i] = (char*) malloc(num_caracteres*sizeof(char));
        strcopy(titulos_linhas[i],nomes_linhas[i]);
    }   
}

// TODO: terminar função desenha_grafico.
void desenha_grafico (int linhas, int colunas, float planilha[][colunas]) {

    char* comando_setar_titulo = "set title ";
    strcat(comando_setar_titulo,titulo_grafico);

    char* comando_plotar_arquivo = "plot ";
    strcat(comando_plotar_arquivo,"");

    char* comando_gnu_plot[] = {comando_setar_titulo, comando_plotar_arquivo};

    FILE *arquivo_gnu = popen("gnuplot -persistent", "w");

}