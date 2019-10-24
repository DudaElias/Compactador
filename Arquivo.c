#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <string.h>

FILE *arq;
unsigned char *vetorDeLetras;
int *frequencias;
int tamanho;
char codigos[256][256];

void criarArvore(NoFila* f)
{
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->esq = pop(f);
    novoNo->dir = pop(f);
    novoNo->vazio = 1;
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
            while(fread(&aux, sizeof(char), 1, arq))
            {
                achou = 0;
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
            //percorrerArvore(f->dado);

            char codigo[200];
            int topo = 0;
            criarTabela(f->dado, codigo, topo);
            criarArquivo(nome);
            //percorrer(f);
        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {

        }
    }

}

void criarTabela(NoArvore* a, char codigo[], int topo)
{
    int i;
    //criar variavel para retornar a tabela
    if(a->esq)
    {
        codigo[topo] = 0;
        criarTabela(a->esq, codigo, topo+1);
    }
    if(a->dir)
    {
        codigo[topo] = 1;
        criarTabela(a->dir, codigo, topo+1);
    }
    if(a->esq == NULL && a->dir == NULL)
    {
        i = 0;
        printf("%c\n", a->letra);
        for(; i< topo; i++)
        {
            printf("%d", codigo[i]);

        codigos[][i] = codigo[i];
        }
        printf("\n");
    }

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

void criarArquivo(char* nome)
{
    FILE* fil;
    unsigned int qtdBytes;
    char* x = strtok(nome, ".");
    fil = fopen(strcat(x, ".dodao"),"wb");
    if(fil == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    int j = 0;
    for()
  //usando fprintf para armazenar a string no arquivo
  fprintf(fil, "%s", "batata");

  //usando fclose para fechar o arquivo
  fclose(fil);

  printf("Dados gravados com sucesso!");
}
