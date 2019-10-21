#include "Fila.h"
#include <stdlib.h>

NoFila create()
{
    NoFila n;
    n.dado = NULL;
    n.prox = NULL;
    return n;
}

void push(NoFila *raiz, NoArvore *dado)
{
    NoFila *fila = raiz;
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->dir = dado->dir;
    novoNo->esq = dado ->esq;
    novoNo->freq = dado->freq;
    novoNo->letra = dado->letra;
    novoNo->vazio = dado->vazio;
    NoFila* novoNoFila = (NoFila*)malloc(sizeof(NoFila));
    novoNoFila->dado = novoNo;

    if(fila->dado == NULL)
        fila->dado = novoNoFila;
    else
    {
        while(fila->prox != NULL)
            fila = fila->prox;
        novoNoFila->prox = fila->prox;
        fila->prox = novoNoFila;

    }

}


NoFila* pop(NoFila *f)
{
    NoArvore *c = f->dado;

    f= f->prox;
    return c;
}
