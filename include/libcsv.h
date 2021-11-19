#ifndef _libcsv_h
#define _libcsv_h

/* Essa função recebe um ponteiro para o arquivo csv
 * e um ponteiro para a variável colunas. Ela guarda
 * nessa variável, a quantidade de colunas da planilha 
 * Retorna 0 se a operação for concluída sem problemas 
 * Returna -1 se, em algum momento houve alguma 
 * inconsistência no arquivo.
*/
int conta_colunas(FILE *fp, int *colunas, float planilha[][1000]);

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
int cria_planilha(FILE *fp, float planilha[1000][1000], int *linhas, int colunas, char *nomes_linhas[1000]);


/* Essa função é auxilia no tratamento de erros da biblioteca.
 * O primeiro valor recebido é um inteiro que, quando -1, indica
 * a ocorrência do erro. São também recebidos uma mensagem para
 * ser exibido quando há presença de erro e também um inteiro
 * indicando se é um erro do sistema operacional, caso o for,
 * mostra também a mensagem devolvida pelo SO.
*/
void tratamento_erro(int codigo, char *mensagem, int erro_so);

/* Apenas para fins de teste.
 * imprime o nome das colunas.
*/
void imprime_nomes(char *nomes[1000], int linhas);

/* Apenas para fins de teste.
 * imprime a planilha os dados.
*/
void imprime_planilha(float planilha[1000][1000], int colunas, int linhas);

#endif