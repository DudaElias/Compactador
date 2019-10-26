#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <string.h>

FILE *arq;
FILE *arqSaida;
unsigned char *vetorDeLetras;
int *frequencias;
int tamanho;
Tabela* codigos;
Tabela* inicio;

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
        printf("N�o foi possivel abrir o arquivo, verifique sua exist�ncia e o caminho");
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

            rewind(arq);
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


            arqSaida = fopen(strcat(nome, ".dao"),"wb");
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }

            codigos = (Tabela*)malloc(tamanho*sizeof(Tabela));
            codigos->prox = NULL;
            codigos->letra = NULL;
            codigos->codigo = NULL;
            int topo = 0;
            char codigo[256];
            criarTabela(f->dado, codigo, topo);
            inicio = (Tabela*)malloc(tamanho*sizeof(Tabela));
            inicio->prox = codigos;
            inicio->letra = NULL;
            inicio->codigo = NULL;
            while(fread(&aux, sizeof(char), 1, arq))
            {
                while(codigos->letra != aux)
                    codigos = codigos->prox;
                if(codigos->letra == aux)
                {
                    int tamanhoCodigosEmByte = 0;
                    char* falta;
                    char byte;
                    char*aux;
                    while(tamanhoCodigosEmByte != 8)
                    {
                        if(codigos->tamanho > 8)
                        {
                            if(falta[0] != NULL)
                                strcat()
                            strncpy(&byte, codigos->codigo, 8 - tamanhoCodigosEmByte);
                            memcpy(aux, &codigos->codigo[codigos->tamanho - (8-tamanhoCodigosEmByte)], sizeof(codigos->tamanho - (8-tamanhoCodigosEmByte)));
                            strcat(falta, aux);
                            fwrite(&byte, sizeof(char), 1, arqSaida);
                        }
                        else if()
                    }
                    free(falta);
                }
                codigos = inicio;
            }
            fclose(arqSaida);
        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {
            int v;
            while(fread(&aux, sizeof(char), 1, arq))
            {
                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                fread(&v, sizeof(int), 1, arq);
                x->freq = v;
                x->letra = (unsigned char)aux;
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(&f, x);
                free(x);

            }
            while(tamanho >= 2)
            {
                criarArvore(f);
            }
            codigos = (Tabela*)malloc(tamanho*sizeof(Tabela));
            codigos->prox = NULL;
            codigos->letra = NULL;
            codigos->codigo = NULL;
            int topo = 0;
            char codigo[256];
            criarTabela(f->dado, codigo, topo);
            inicio = (Tabela*)malloc(tamanho*sizeof(Tabela));
            inicio->prox = codigos;
            inicio->letra = NULL;
            inicio->codigo = NULL;
            criarTabela(f->dado, codigo, topo);
            while(fread(&aux, sizeof(char), 1, arq))
            {
                char v;
                int j=0;
                for(;j<codigos->tamanho;j++)
                {
                    v =  aux << j * 8;
                    fwrite(&v, sizeof(char),1, arqSaida);
                }
                if(codigos->letra == aux)
                {
                    int j = 0;
                    char v;
                    for(;j<codigos->tamanho;j++)
                    {
                        v =  codigos->codigo[j] >> j * 8;
                        fwrite(&v, sizeof(char),1, arqSaida);
                    }
                }
                while(codigos->codigo != aux)
                    codigos = codigos->prox;
                codigos = inicio;
            }

            fclose(arq);



        }
    }

}

void criarTabela(NoArvore* a, char codigo[], int topo)
{
    int i;

    if(a->esq)
    {
        codigo[topo] = '0';
        criarTabela(a->esq, codigo, topo+1);
    }
    if(a->dir)
    {
        codigo[topo] = '1';
        criarTabela(a->dir, codigo, topo+1);
    }
    if(a->esq == NULL && a->dir == NULL)
    {
        Tabela *ta = codigos;
        i = 0;
        char* codigoReal = (char*)malloc(topo * sizeof(char));
        for(; i< topo; i++)
        {
            codigoReal[i] = codigo[i];

            printf("%c", codigoReal[i]);
        }
        printf("%c\n", a->letra);

        fwrite(&a->letra, sizeof(char), 1, arqSaida);
        fwrite(codigoReal, sizeof(char), topo, arqSaida);
        Tabela* t = (Tabela*)malloc(sizeof(Tabela));
        t->codigo = codigoReal;
        t->letra =  a->letra;
        t->prox = NULL;
        t->tamanho = topo;

        if(ta->codigo == NULL)
        {
            ta->codigo = codigoReal;
            ta->letra = a->letra;
            ta->tamanho = topo;
            ta->prox = NULL;
        }
        else
        {
            while(ta->prox != NULL)
            {
                ta = ta->prox;
            }
            t->prox = ta->prox;
            ta->prox = t;
        }
        free(codigoReal);
    }

}

void percorrerArvore(NoArvore* a)
{
    if(a == NULL)
        return;
    percorrerArvore(a->esq);
    Letra t;
    t.letra = a->letra;
    t.freq = a->freq;
    int j = 0;
    char v;
    fwrite(&a->letra, sizeof(char), 1, arqSaida);
    for(;j<4;j++)
    {
        v = a->freq >> j * 8;
        fwrite(&v, sizeof(char),1, arqSaida);
    }
    percorrerArvore(a->dir);
}

/*void criarArquivo(char* nome)
{
    FILE* fil;
    unsigned int qtdBytes;
    char* x = strtok(nome, ".");
    fil = fopen(strcat(x, ".dao"),"wb");
    if(fil == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    percorrerArvore(->dado);
    char y;
    byte inserir;
    int i = 0;
    while(fread(&y, sizeof(char), 1, arq))
    {
        for(;codigos->prox != NULL && codigos->letra != y; codigos = codigos->prox)
        {}
        inserir = inserir | (1 << i * 8);
        tamanho++;
    }

}*/
