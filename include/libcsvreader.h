#ifndef _libcsvreader_h
#define _libcsvreader_h

/* Essa função recebe no parâmetro caminho dos dados
 * o nome completo do local de onde um arquivo .csv 
 * com os dados vai ser buscado. Em seguida, ela lê
 * esse arquivo, guardando em uma matriz na memória.
 * Após buscar o arquivo .csv e processá-lo, a função 
 * devolve o tamanho da planilha (matriz) nos parâmetros
 * *linhas e *colunas. Além disso, um apontador para um
 * vetor de strings contendo os nomes das linhas da
 * será devolvido em nomes linhas.
*/
void carrega_dados (char *caminho_dos_dados, int *linhas, int *colunas, float planilha[1000][1000], char *nomes_linhas[1000]);

#endif