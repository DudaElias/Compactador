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
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->esq = pop(f);
    novoNo->dir = pop(f);
    novoNo->freq = novoNo->esq->freq + novoNo->dir->freq;
    novoNo->letra= NULL;
    push(&f, novoNo);
    free(novoNo);
    tamanho--;
}

void lerArq(char *nome, char tipo)
{
    if( (arq = fopen(nome, "rb")) == NULL)
    {
        printf("Não foi possivel abrir o arquivo, verifique sua existência e o caminho");
    }
    else
    {
        NoFila* f = create();
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
            j = 0;
            while(tamanho >= 2)
            {
                criarArvore(f);
            }
            percorrerArvore(f->dado);
            //percorrer(f);
        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {

        }
    }

}

//fazer tabela codigos
void criarTabela(NoArvore* a)
{
    char codigo[];
    char caracter[];
    int i;

    if(a == NULL)
        return;

    while(a->)

    for(i = 0; 0==0 ; i++)
    {
        codigo[i] = '0';
        percorrerArvore(a->esq);
        if(a->esq == NULL && a->dir == NULL)
        {
            codigo[i]= NULL;
            //voltar ponteiro pro anterior
        }
        codigo[i] = '1';
        percorrerArvore(a->dir);
    }
/*
    while(a->esq != NULL && a->dir != NULL)
    {
        codigo[] = '0';
        percorrerArvore(a->esq);
        codigo[] = '1';
        percorrerArvore(a->dir);
    }*/


}

void percorrerArvore(NoArvore* a)
{
    if(a == NULL)
        return;
    percorrerArvore(a->esq);
    printf("%c\t", a->letra);
    printf("%d\n\n", a->freq);
    percorrerArvore(a->dir);
}
