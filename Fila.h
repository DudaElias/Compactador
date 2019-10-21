typedef struct FilaOriginal{
    int tamanho;
    void *dados;
    int *primeiro;
    int *ultimo;
    int dadosSalvos;
} FilaOriginal;


typedef struct No
{
    char letra;
    char vazio;
    int freq;
    struct NoArvore *esq, *dir;

}
No;

extern void create(FilaOriginal *f, int t, int tamanhoDado);
extern void push(FilaOriginal *f, No *dado);
extern No pop(FilaOriginal *f);
