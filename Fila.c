#include "Fila.h"
#include <stdlib.h>

void create(Fila** f) // cria a fila
{
    (*f) = (Fila*)malloc(sizeof(Fila));
    (*f)->primeiro = NULL;
}

void push(Fila **raiz, NoArvore *dado)
{

    NoFila* in;//e o no em que esta no momento
    NoFila* out;//eh o no que vem antes de in
    if((*raiz)->primeiro == NULL) // caso seja o primeiro dado a ser inserido
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
        while(in != NULL && !achou) // enquanto n tiver encontrado o lugar
        {
            if(dado->freq < in->dado->freq) // verifica se a freq do dado eh menor que a do que esta no momento
            {
                NoFila* inserido = (NoFila*)malloc(sizeof(NoFila)); // insere o dado na fila, entre in e out
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
        if(!achou) // caso não tenha encontrado insere ao fim da fila
        {
            NoFila* inserido = (NoFila*)malloc(sizeof(NoFila));
            inserido->dado = dado;
            inserido->prox = NULL;
            out->prox = inserido;
        }
    }

}

NoArvore* pop(Fila *f)
{

    if(f->primeiro == NULL){ // caso esteja vazio retorna o valor default
        return NULL;
    }

    NoArvore* c = f->primeiro->dado; // armazena o valor do dado a ser retirado em um aux
    NoFila *t = f->primeiro;
    f->primeiro = f->primeiro->prox; // retira o valor
    free(t); // libera o local de memoria onde estava o retirado
    return c; // retorna o valor do retirado
}
