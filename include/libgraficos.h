#ifndef _libgraficos_h
#define _libgraficos_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NUM_PAISES 5

char *titulo_grafico = NULL;
char *rotulo_x = NULL;
char *rotulo_y = NULL;
char **titulos_linhas = NULL;
int num_linhas, num_colunas;

//TODO: mudar funções auxiliares para arquivos .h e .c separados.

/* Função define_num_linhas:
* Uso: define_num_linhas(int*)
* -----------------------------
* Esta função define o número de linhas que o gráfico irá conter.*/
void define_num_linhas(int *linhas);

/* Função define_num_colunas:
* Uso: define_num_colunas(int*)
* -----------------------------
* Esta função define o número de colunas que o gráfico irá conter.*/
void define_num_colunas(int *colunas);

/* Função define_titulo:
* Uso: define_titulo(char*)
* -----------------------------
* Esta função define o título de um gráfico*/
void define_titulo (char *titulo);

/* Função define_rotulo_x:
* Uso: define_rotulo_x(char*)
* -----------------------------
* Esta função define o rótulo do eixo x do gráfico a ser analisado.*/
void define_rotulo_x (char *nome);

/* Função define_rotulo_y:
* Uso: define_rotulo_y(char*)
* -----------------------------
* Esta função define o rótulo do eixo y do gráfico a ser analisado.*/
void define_rotulo_y (char *nome);

/* Função define_nome_linhas:
* Uso: define_nomes_linhas(char*[])
* -----------------------------
* Esta função define o nome das linhas de um gráfico*/
void define_nomes_linhas (char *nomes_linhas[]);

/* Função desenha_grafico:
* Uso: desenha_grafico(int, int, float**)
* -----------------------------
* Esta função desenha o gráfico*/
void desenha_grafico (int linhas, int colunas, float planilha[][colunas]);

#endif