/* Esse arquivo é a implementação da
 * biblioteca csv externa 
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <curl/curl.h>


/* variável externa que contém o código do último 
 * erro emitido pelo sistema operacional.
*/
extern int errno;

/* Essa função recece um ponteiro para o arquivo 
 * csv e passa posição atual de leitura para a 
 * próxima célula.
 * Ela retorna 0 se o último char lido for ','
 * Ela retorna 1 se o última char lido for um '\n'
 * Ela retorna -1 se, em algum momento, atingir o fim do arquivo
*/
int pula_celula(FILE *fp) {
    int fim_arq;
    char c = '*';
    while((fim_arq = fscanf(fp, "%c", &c)) != EOF 
        && c != ',' && c != '\n') {}
    if(fim_arq == EOF) return -1;
    if(c == '\n') return 1;
    return 0;
}

/* Essa função recebe um ponteiro para o arquivo csv
 * e um ponteiro para a variável colunas. Ela guarda
 * nessa variável, a quantidade de colunas da planilha 
 * Ela retorna 0 se a operação for concluída sem problemas 
 * Ela returna -1 se, em algum momento houve alguma 
 * inconsistência no arquivo.
*/
int conta_colunas(FILE *fp, int *colunas) {
    int numero_colunas = 0;
    int fim_arq;
    while((fim_arq = pula_celula(fp)) == 0) numero_colunas++;
    if(numero_colunas > 1000 || numero_colunas <= 0 
        || fim_arq == -1) return -1;
    *colunas = numero_colunas;
    return 0; 
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
int cria_planilha(FILE *fp, float planilha[1000][1000], int *linhas, int colunas) {
    char c = '*';
    int numero_linhas = 0;

    // Pula a primeira célula da linha que contém um nome
    while(pula_celula(fp) != -1) {
        int i;
        int fim_arq;
        for(i = 0; i < colunas; i++) {
            /* Lê o próximo char. Sai do loop se for atingido o
             * fim do arquivo
            */
            if((fim_arq = fscanf(fp, "%c", &c)) == EOF) break;

            // Célula vazia
            if(c == ',' || c == '\n') planilha[numero_linhas][i] = 0.0;

            else {
                // Volta uma posicao no arquivo
                fseek(fp, -1L, SEEK_CUR);
                // Salva o valor
                fscanf(fp, "%f", &planilha[numero_linhas][i]);
                // Pula o próximo char ','
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

/* Essa função é auxilia no tratamento de erros da biblioteca.
 * O primeiro valor recebido é um inteiro que, quando -1, indica
 * a ocorrência do erro. São também recebidos uma mensagem para
 * ser exibido quando há presença de erro e também um inteiro
 * indicando se é um erro do sistema operacional, caso o for,
 * mostra também a mensagem devolvida pelo SO.
*/
void tratamento_erro(int codigo, char *mensagem, int erro_so) {
    if(codigo == -1) {
        if(erro_so)
            perror(mensagem);
        else {
            fprintf(stderr, "%s\n", mensagem);
        }
        exit(EXIT_FAILURE);
    }
}


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000]) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "http://www.ime.usp.br/~kon/tmp/BRICS_PIBPerCapita.csv";
    char outfilename[FILENAME_MAX] = "/tmp/temporary.csv";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl); 
        fclose(fp);

        fp = fopen("/tmp/temporary.csv", "r");

        if (fp == NULL) {
            tratamento_erro(-1, "Erro ao abrir arquivo", 1);
        }    
        tratamento_erro(conta_colunas(fp, colunas), "Erro ao criar a planilha. Formato inválido.", 0);
        tratamento_erro(cria_planilha(fp, planilha, linhas, *colunas), "Erro ao criar a planilha. Formato inválido.", 0);

        fclose(fp);

    }
    
}