#ifndef _libgraficos_h
#define _libgraficos_h

/* Função define_num_linhas:
* Uso: define_num_linhas(int*)
* -----------------------------
* Esta função define o número de linhas que o gráfico irá conter.*/
void define_num_linhas(int linhas);

/* Função define_num_colunas:
* Uso: define_num_colunas(int*)
* -----------------------------
* Esta função define o número de colunas que o gráfico irá conter.*/
void define_num_colunas(int colunas);

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

/* Função desaloca_string:
* Uso: desaloca_string(char*)
* -----------------------------
* Esta função desaloca a memória alocada para a string passada como parâmetro. */
void desaloca_string(char* str);

/* Função desaloca_vetor_strings:
* Uso: desaloca_vetor_strings(char**)
* -----------------------------
* Esta função desaloca a memória alocada para o vetor de strings passado como
* parâmetro.                                                                   */
void desaloca_vetor_strings(char** strs);

/* Função desenha_grafico:
* Uso: desenha_grafico(int, int, float**)
* -----------------------------
* Esta função desenha o gráfico em um arquivo .png ou em formato de texto, na 
* saída padrão.                                                                */
void desenha_grafico (int linhas, int colunas, float planilha[][colunas]);

#endif