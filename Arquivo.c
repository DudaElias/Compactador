#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"


FILE *arq;
unsigned char *vetorDeLetras;
int *frequencias;
int tamanho;


void criarArvore(NoFila* f)
{
    NoFila* novoNo=(NoFila*)malloc(sizeof(NoFila));
    int frequen;

    frequen = f->dado->freq + f->prox->dado->freq;
    novoNo->dado->freq = frequen;

    novoNo->dado->dir = f->prox->dado;
    novoNo->dado->esq = f->dado;

    novoNo->prox = f->prox->prox;
}

void lerArq(char *nome, char tipo)
{
    if( (arq = fopen(nome, "rb")) == NULL)
    {
        printf("Não foi possivel abrir o arquivo, verifique sua existência e o caminho");
    }
    else
    {
        NoFila f = create();
        tamanho = 0;
        int i = 0;
        int dados = 0;
        unsigned char aux;
        vetorDeLetras = (unsigned char*)malloc(256*sizeof(char));
        frequencias = (int*)malloc(256*sizeof(int));

        if(tipo == 'c')
        {
            char achou;
            while(!feof(arq))
            {
                achou = 0;
                fread(&aux, sizeof(char), 1, arq);
                if(tamanho == 0)
                {
                    vetorDeLetras[tamanho] = aux;
                    frequencias[tamanho] = 1;
                    tamanho++;
                }
                else
                {
                    for(;i<tamanho;i++)
                    {
                        if(vetorDeLetras[i] == aux)
                        {
                            frequencias[i]++;
                            achou = 1;
                        }
                    }
                    i = 0;
                    if(achou == 0)
                    {
                        vetorDeLetras[tamanho] = aux;
                        frequencias[tamanho] = 1;
                        tamanho++;
                    }
                }

            }
            fclose(arq);
            int j = 0;
            for(;j < tamanho;j++)
            {
                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                x->freq = (int)frequencias[j];
                x->letra = (unsigned char)vetorDeLetras[j];
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(&f, x);
                free(x);
            }
            criarArvore(&f);
            j = 0;
            for(;j <tamanho;j++)
            {
                NoArvore* x = pop(&f);
                printf("%c\n", (unsigned char)x->letra);
                printf("%d\n", (int)x->freq);
            }
            //percorrer(&f);
        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {
        }
    }

}
