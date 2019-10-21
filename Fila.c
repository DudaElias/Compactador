#include "Fila.h"
#include <stdlib.h>

NoFila create()
{
    NoFila n;
    n.dado = NULL;
    n.prox = NULL;
    return n;
}

void push(NoFila *raiz, NoFila *dado)
{
    NoFila *fila = raiz;
    NoFila *dadoNovo = (NoFila*)malloc(sizeof(NoFila));
    dadoNovo->dado->letra = dado->dado->letra;
    dadoNovo->dado->freq = dado->dado->freq;
    dadoNovo->dado->dir = dado->dado->dir;
    dadoNovo->dado->esq = dado->dado->esq;
    dadoNovo->dado->vazio = dado->dado->vazio;

    if(fila->dado == NULL)
        fila->dado = dadoNovo;
    else
    {
        while(fila->dado != NULL)
            fila = fila->prox;
        dadoNovo->prox = fila->prox;
        fila->prox = dadoNovo;

    }

}


NoFila* pop(FilaOriginal *f)
{
    No *c = f->dados[*(f->primeiro++)];

    if(f->primeiro == f->tamanho)
        f->primeiro = 0;

    f->dadosSalvos--;
    return c;
}
