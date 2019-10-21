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
        FilaOriginal *f;
        create(f, tamanho, sizeof(char));
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
            for(;j <= tamanho;j++)
            {
                No *x;
                x->freq = frequencias[j];
                x->letra = vetorDeLetras[j];
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(f, x);
            }
            j = 0;
            for(;j <=tamanho;j++)
                printf("%c", pop(f));

        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {


        }
    }

}
