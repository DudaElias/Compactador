#include "Fila.h"
#include <stdlib.h>

void create(Fila** f)
{
    (*f) = (Fila*)malloc(sizeof(Fila));
    (*f)->primeiro = NULL;
}

void push(Fila **raiz, NoArvore *dado)
{

    NoFila* in;
    NoFila* out;
    if((*raiz)->primeiro == NULL)
    {
        (*raiz)->primeiro = (NoFila*)malloc(sizeof(NoFila));
        (*raiz)->primeiro->dado = dado;
        (*raiz)->primeiro->prox = NULL;
    }

    else
    {

        char achou = 0;

        in = (*raiz)->primeiro;
        out = NULL;
        while(in != NULL && !achou)
        {
            if(dado->freq < in->dado->freq)
            {
                NoFila* inserido = (NoFila*)malloc(sizeof(NoFila));
                inserido->dado = dado;
                inserido->prox = in;
                if(out != NULL)
                    out->prox = inserido;
                else
                    (*raiz)->primeiro = inserido;
                achou = 5;
            }
            out = in;
            in = in->prox;
        }
        if(!achou)
        {
            NoFila* inserido = (NoFila*)malloc(sizeof(NoFila));
            inserido->dado = dado;
            inserido->prox = NULL;
            out->prox = inserido;
        }
    }

}


void percorrer(NoFila *f)
{
    NoFila* n = f;
    while(n != NULL)
    {
        printf("%c\n", n->dado->letra);
        printf("%d\n", n->dado->freq);
        putchar('\n');
        n = n->prox;
    }

}

NoArvore* pop(Fila *f)
{
    //NoFila* temp = fila->primeiro;
    //fila->primeiro = fila->primeiro->prox;

    if(f->primeiro == NULL){
        return NULL;
    }

    NoArvore* c = f->primeiro->dado;
    NoFila *t = f->primeiro;
    f->primeiro = f->primeiro->prox;
    free(t);
    return c;
}
