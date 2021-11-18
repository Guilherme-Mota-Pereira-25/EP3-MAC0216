int conta_colunas(FILE *fp, int *colunas, float planilha[][1000]);

int cria_planilha(FILE *fp, float planilha[1000][1000], int *linhas, int colunas, char *nomes_linhas[1000]);

void imprime_planilha(float planilha[1000][1000], int colunas, int linhas);

void tratamento_erro(int codigo, char *mensagem, int erro_so);

void imprime_nomes(char *nomes[1000], int linhas);