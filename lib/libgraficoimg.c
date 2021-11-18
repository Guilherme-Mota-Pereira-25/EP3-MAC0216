#include "../include/libgraficos.h"

//TODO: mudar funções auxiliares para arquivos .h e .c separados.
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

    const int num_comandos = 5;

    // Primeiramente, vamos montar um arquivo com os dados na formatação cor-
    // reta para poder ser processado pelo gnuplot.
    FILE* dados_formatados = fopen("/tmp/dados.dat", 'w');
    
    for (int j = 0; j < num_colunas; j++) {
        for (int i = 0; i < num_linhas; i++) {
            fprintf(dados_formatados,"%f ", planilha[i][j]);
        }
        fprintf(dados_formatados, "\n");
    }

    // Agora vamos montar o arquivo com os comandos do gnuplot a serem executados.
    FILE* especific_gnu = fopen("/tmp/especific_gnu.", 'w');

    char* comando_setar_titulo = "set title ";
    strcat(comando_setar_titulo, titulo_grafico);

    char* comando_setar_saida = "set output \"grafico.png\"";

    char* comando_setar_rotulo_x = "set xlabel ";
    strcat(comando_setar_rotulo_x, rotulo_x);
    
    char* comando_setar_rotulo_y = "set ylabel ";
    strcat(comando_setar_rotulo_y, rotulo_y);

    char* comando_plotar = "plot ";

    char* config_plot_brasil     = "\"dados.dat\" using 1:2 title \"Brazil\" linetype 7 linecolor \"green\" with linespoints,";
    char* config_plot_china      = "\"dados.dat\" using 1:3 title \"China\" linetype 7 linecolor \"red\" with linespoints,";
    char* config_plot_india      = "\"dados.dat\" using 1:4 title \"India\" linetype 7 linecolor \"#FF5733\" with linespoints,";
    char* config_plot_russia     = "\"dados.dat\" using 1:5 title \"Russian Federation\" linetype 7 linecolor \"blue\" with linespoints,";
    char* config_plot_africa_sul = "\"dados.dat\" using 1:6 title \"South Africa\" linetype 7 linecolor 0 with linespoints";

    char* configs_plot[] = {config_plot_brasil, config_plot_china, config_plot_india, config_plot_russia, config_plot_africa_sul};

    for (int i = 0; i < NUM_PAISES; i++) {
        strcat(comando_plotar, configs_plot[i]);
    }

    char* comandos_gnu[] = { comando_setar_titulo, 
                             comando_setar_saida,
                             comando_setar_rotulo_x,
                             comando_setar_rotulo_y,
                             comando_plotar
                            };
    
    for (int i = 0; i < num_comandos; i++) {
        fprintf(especific_gnu, comandos_gnu[i]);
        fprintf(especific_gnu, "\n");
    }

    // TODO: executar comandos do gnuplot com a função execvp, para montar o gráfico.
    // execvp();

    fclose(dados_formatados);
    fclose(especific_gnu);
}