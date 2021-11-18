
int pula_celula(FILE *fp);

int conta_colunas(FILE *fp, int *colunas);

int cria_planilha(FILE *fp, float planilha[1000][1000], int *linhas, int colunas);

void imprime_planilha(float planilha[1000][1000], int colunas, int linhas);

void tratamento_erro(int codigo, char *mensagem, int erro_so);