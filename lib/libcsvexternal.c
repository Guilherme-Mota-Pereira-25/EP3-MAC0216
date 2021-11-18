/* Esse arquivo é a implementação da
 * biblioteca csv externa 
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "libcsv.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000], char *nomes_linhas[1000]) {

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
        tratamento_erro(conta_colunas(fp, colunas, planilha), "Erro ao criar a planilha. Formato inválido.", 0);
        tratamento_erro(cria_planilha(fp, planilha, linhas, *colunas, nomes_linhas), "Erro ao criar a planilha. Formato inválido.", 0);

        /*printf("colunas: %d", *colunas);
        printf(" linhas: %d\n", *linhas);
        imprime_planilha(planilha, *colunas, *linhas);
        imprime_nomes(nomes_linhas, *linhas);*/
        fclose(fp);

    }
    
}