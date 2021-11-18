
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

// Labels para tipos de chars importantes
enum {virgula, newline, letra, digito, outro, eof=-1} char_code;
enum {erro = -1, ok} status_funcao;
#define MAX_COLUNAS 1000
#define MAX_LINHAS 1000
// Número máximo de chars para uma celula com texto
#define MAX_STR 50
// Valor padrão para uma célula vazia
#define CELULA_VAZIA -1

/* variável externa que contém o código do último 
 * erro emitido pelo sistema operacional.
*/
extern int errno;


/* Essa função revebe um ponteiro para o arquivo csv
 * e retorna um código referente ao próximo char lido 
 * Retorna virgula se char = ','
 * Retorna newline se char = '\n'
 * Retorna letra se char for uma letra
 * Retorna digito se char for um digito 
 * Retorna eof se não conseguir ler 
*/
int proximo_char(FILE *fp) {
    char c = '*';

    if(fscanf(fp, "%c", &c) == erro) return eof;

    int tipo_char = outro;
    if(c == ',') tipo_char = virgula;
    if(c == '\n') tipo_char = newline;
    if(isalpha(c)) tipo_char = letra;
    if(isdigit(c) ||  c == '-' || c == '.') tipo_char = digito;
    // Volta um char no arquivo
    fseek(fp, -1L, SEEK_CUR);
    return tipo_char;
}

/*
 * Essa função lê uma célula de texto e 
 * retorna o seu valor em uma string
*/
char* le_texto_celula(FILE* fp) {
    char *texto = malloc(sizeof(char) * MAX_STR);
    char prox_char;
    int i;
    for(i = 0; (prox_char = proximo_char(fp)) != newline &&
        prox_char != virgula && prox_char != eof &&
        i < MAX_STR-1; i++) {
            fscanf(fp, "%c", &texto[i]);
    }
    texto[i] = '\0';
    return texto;
}

/* Essa função recebe um ponteiro para o arquivo csv
 * e um ponteiro para a variável colunas. Ela guarda
 * nessa variável, a quantidade de colunas da planilha 
 * Retorna 0 se a operação for concluída sem problemas 
 * Returna -1 se, em algum momento houve alguma 
 * inconsistência no arquivo.
*/
int conta_colunas(FILE *fp, int *colunas, float planilha[MAX_LINHAS][MAX_COLUNAS]) {
    int numero_colunas = 0;

    // Pula primeira celula
    le_texto_celula(fp);
    if(proximo_char(fp) == eof) return erro;
    
    int prox_char = 0;
    while((prox_char = proximo_char(fp)) == virgula) {
        // Pula o ','
        fseek(fp, 1L, SEEK_CUR);

        if((prox_char = proximo_char(fp)) == digito)  
            fscanf(fp, "%f", &planilha[0][numero_colunas]);
        else if(prox_char == virgula || prox_char == newline) 
            planilha[0][numero_colunas] = 0.0;
        else return erro;
        numero_colunas++;
    }
    if(numero_colunas > MAX_COLUNAS || numero_colunas <= 0 
        || prox_char == eof) return erro;

    *colunas = numero_colunas;
    return ok; 
}




/* Essa função recece um ponteiro para o arquivo csv,
 * a quantidade de colunas do csv, um ponteiro para
 * a variável das linhas e uma matriz para os dados da
 * planilha. Ela lê os dados do arquivo e guarda a 
 * quantidade de linhas e os dados das planilha nas 
 * suas respectivas variáveis.  
 * Ela retorna 0 se a operação for concluída sem problemas 
 * Ela returna -1 se, em algum momento houve alguma 
 * inconsistência no arquivo.
*/
int cria_planilha(FILE *fp, float planilha[MAX_LINHAS][MAX_COLUNAS], int *linhas, int colunas, char *nomes_linhas[MAX_LINHAS]) {
    int numero_linhas = 1;

    int prox_char;
    while(proximo_char(fp) == newline) {
        //Pula o '\n'
        fseek(fp, 1L, SEEK_CUR);

        char *str = le_texto_celula(fp);
        if(proximo_char(fp) == eof) break;
        
        nomes_linhas[numero_linhas-1] = str;
        int i;
        for(i = 0; i < colunas; i++) {
            if(proximo_char(fp) == virgula) {
                //Pula o ','
                fseek(fp, 1L, SEEK_CUR);
                if((prox_char = proximo_char(fp)) == digito) {
                    fscanf(fp, "%f", &planilha[numero_linhas][i]);
                } else if(prox_char == virgula || prox_char == newline) {
                    planilha[numero_linhas][i] = CELULA_VAZIA;
                } else {
                    return erro;
                }

            } else {
                return erro;
            }
        }

        numero_linhas++;
    }
    if(numero_linhas > MAX_LINHAS || numero_linhas <= 0) return erro;
        *linhas = numero_linhas;

    return 0;
}

/* Apenas para fins de teste.
 * imprime a planilha os dados.
*/
void imprime_planilha(float planilha[MAX_LINHAS][MAX_COLUNAS], int colunas, int linhas) {
    int i;
    int j;
    printf("planilha: \n");
    for(i = 0; i < linhas; i++) {
        for(j = 0; j < colunas; j++) {
            printf("%.1f,", planilha[i][j]);
        }
        printf("\n");
    }
}

void imprime_nomes(char *nomes[MAX_LINHAS], int linhas) {
    int i;
    printf("Nomes: \n");
    for(i = 0; i < linhas-1; i++) {
        printf("%s ", nomes[i]);
    }
}

/* Essa função é auxilia no tratamento de erros da biblioteca.
 * O primeiro valor recebido é um inteiro que, quando -1, indica
 * a ocorrência do erro. São também recebidos uma mensagem para
 * ser exibido quando há presença de erro e também um inteiro
 * indicando se é um erro do sistema operacional, caso o for,
 * mostra também a mensagem devolvida pelo SO.
*/
void tratamento_erro(int codigo, char *mensagem, int erro_so) {
    if(codigo == erro) {
        if(erro_so)
            perror(mensagem);
        else {
            fprintf(stderr, "%s\n", mensagem);
        }
        exit(EXIT_FAILURE);
    }
}