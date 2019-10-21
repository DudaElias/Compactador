
#include "Fila.h"

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


void create(FilaOriginal *f, int t, int tamanhoDado)
{
    f->tamanho = t;
    f->dadosSalvos = 0;
    f->primeiro = 0;
    f->ultimo = -1;
    f->dados = malloc(f->tamanho*tamanhoDado);
}

void push(FilaOriginal *f, No *dado)
{
    f->dados[f->ultimo + 1] = dado;
    f->ultimo++;
    f->tamanho++;
}


No pop(FilaOriginal *f)
{
    No *c = f->dados[f->primeiro++];

    if(f->primeiro == f->tamanho)
        f->primeiro = 0;

    f->dadosSalvos--;
    return c;
}
