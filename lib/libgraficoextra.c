#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//TODO: mudar funções auxiliares para arquivos .h e .c separados.
//TODO: comentar as funções a seguir.

char *titulo_grafico = NULL;
char *rotulo_x = NULL;
char *rotulo_y = NULL;

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

void escreve_dados(FILE* dados, float planilha[1000][1000], int colunas, int linhas) {
    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas; i++) {
            fprintf(dados, "%f ", planilha[i][j]);
        }
        fprintf(dados, "\n");
    }
}

void escreve_parametro(FILE* specs, char *parametro, char* nome_parametro) {
    char spec_gnuplot[100];
    strcpy(spec_gnuplot, "set ");
    strcat(spec_gnuplot, parametro);
    strcat(spec_gnuplot, " \'");
    strcat(spec_gnuplot, nome_parametro);
    strcat(spec_gnuplot, "\'\n");
    fprintf(specs, "%s", spec_gnuplot);
}

void escreve_specs(FILE* specs, int linhas, char *nomes_linhas[1000]) {
    fprintf(specs, "set term qt persist size 700,500\n");
    fprintf(specs, "set output \'graph.png\'\n");
    fprintf(specs, "set datafile missing \'-1.000000\'\n");
    fprintf(specs, "set key outside\n");

    escreve_parametro(specs, "title", titulo_grafico);
    escreve_parametro(specs, "xlabel", rotulo_x);
    escreve_parametro(specs, "ylabel", rotulo_y);
    
    fprintf(specs, "plot ");
    for(int i = 2; i < linhas+1; i++) {
        fprintf(specs, "\'/tmp/dados.dat\' using 1:%d title \'%s\'", i, nomes_linhas[i-2]);
        if(i != linhas+1) fprintf(specs, ", ");
    }
    fprintf(specs, "\n");
}

void desenha_grafico (int linhas, int colunas, float planilha[1000][1000], char *nomes_linhas[1000]) {

    // Primeiramente, vamos montar um arquivo com os dados na formatação cor-
    // reta para poder ser processado pelo gnuplot.
    FILE* dados = fopen("/tmp/dados.dat", "w");
    if(dados == NULL) {
        printf("Erro ao criar .dat");
        exit(1);
    }

    escreve_dados(dados, planilha, colunas, linhas);

    FILE* specs = fopen("/tmp/specs.plg", "w");
    if(specs == NULL) {
        printf("Erro ao criar script_plot.plg");
        exit(1);
    }
    
    escreve_specs(specs, linhas, nomes_linhas);

    fclose(dados);
    fclose(specs);

    char* argument_list[] = {"gnuplot", "/tmp/specs.plg", NULL};
    execvp("gnuplot", argument_list);
    perror("gnuplot");

}

