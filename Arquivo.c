#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"


FILE *arq;
char *vetorDeLetras;
int *frequencias;
int tamanho;
void lerArq(char *nome, char tipo)
{
    if( (arq = fopen(nome, "r")) == NULL)
    {
        printf("Não foi possivel abrir o arquivo, verifique sua existência e o caminho");
    }
    else
    {
        NoFila f = create();
        tamanho = 0;
        int i = 0;
        char aux;
        vetorDeLetras = (char*)malloc(15000*sizeof(char));
        frequencias = (int*)malloc(15000*sizeof(int));

        if(tipo == 'c')
        {
            char achou;
            while(!feof(arq))
            {
                achou = 0;
                aux = getc(arq);
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
            int j = 0;
            for(;j < tamanho;j++)
            {

                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                x->freq = frequencias[j];
                x->letra = vetorDeLetras[j];
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                NoFila *no = (NoFila*)malloc(sizeof(NoFila));
                no->dado = (NoArvore*)malloc(sizeof(NoArvore));
                no->prox = (NoArvore*)malloc(sizeof(NoArvore));
                no->dado = x;
                no->prox = NULL;
                push(&f, no);
                free(x);
                free(no);
            }
            j = 0;
            for(;j <tamanho-1;j++)
            {
                printf("%c", pop(&f)->letra);
                printf("%d", pop(&f)->freq);
                /*printf("%c", vetorDeLetras[j]);
                printf("%d\n", frequencias[j]);*/
            }

        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {


        }
    }

}
