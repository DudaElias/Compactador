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
        fila->dado = novoNoFila->dado;
    else
    {
        while(fila->prox != NULL)
            fila = fila->prox;
        novoNoFila->prox = fila->prox;
        fila->prox = novoNoFila;

    }

}


void percorrer(NoFila *f)
{
    NoFila* n = f;
    while(n->prox != NULL)
    {
        printf("%u\n", n->dado->letra);
        printf("%d\n", n->dado->freq);
        n = n->prox;
    }

}

NoArvore* pop(NoFila *f)
{
    NoArvore *c = (NoArvore*)malloc(sizeof(NoArvore));
    c->dir = f->dado->dir;
    c->esq = f->dado ->esq;
    c->freq = f->dado->freq;
    c->letra = f->dado->letra;
    c->vazio = f->dado->vazio;
    f->dado = f->prox->dado;
    f->prox = f->prox->prox;
    return c;
}
