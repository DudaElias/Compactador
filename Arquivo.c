#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <string.h>
#include <math.h>

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

void criarArvoreD(char letra[], int posicao[]){
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    int i;
    for(i=0;letra!=NULL;i++){
        novoNo->letra = letra[i];
        for(;;){
            //separar pra ler um numero de cada vez
            if(posicao[i]==1){
                    novoNo = novoNo->esq;
            }
            else
            novoNo=novoNo->dir;
        }
    }
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
            fwrite(" ", sizeof(char), 1, arqSaida);
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
            int tamanhoCodigoEmByte = 8;
            char* falta;
            unsigned char byte = 0;
            char aux;
            int codigoAtual = 0;
            inicio->codigo = NULL;
            while(fread(&aux, sizeof(char), 1, arq))
            {
                while(codigos->letra != aux)
                    codigos = codigos->prox;
                if(codigos->letra == aux)
                {
                    int v;
                    if(tamanhoCodigoEmByte != 0)
                    {
                        int i = 0;
                        for(;i<codigos->tamanho; i++)
                        {
                            if(codigos->codigo[i] == '1')
                                codigoAtual += pow(2,(codigos->tamanho-1 - i));
                        }
                        if(tamanhoCodigoEmByte - codigos->tamanho >= 0)
                        {
                            byte = byte << codigos->tamanho;
                            byte += codigoAtual;
                            tamanhoCodigoEmByte -=codigos->tamanho;
                            codigoAtual = 0;
                        }
                        else
                        {
                            byte = byte << tamanhoCodigoEmByte;
                            byte += codigoAtual >>(codigos->tamanho - tamanhoCodigoEmByte);
                            int t = codigos->tamanho - tamanhoCodigoEmByte;
                            fwrite(&byte, sizeof(char),1, arqSaida);
                            byte = 0;
                            byte += codigoAtual << codigos->tamanho + tamanhoCodigoEmByte;
                            byte = byte >> codigos->tamanho + tamanhoCodigoEmByte;
                            tamanhoCodigoEmByte = 8;
                            tamanhoCodigoEmByte -=t;
                            codigoAtual = 0;
                        }
                    }
                    if(tamanhoCodigoEmByte == 0)
                    {
                        fwrite(&byte, sizeof(char),1,arqSaida);
                        byte = 0;
                        tamanhoCodigoEmByte = 8;
                    }
                }
                codigos = inicio;
            }
            if(tamanhoCodigoEmByte != 8)
            {
                byte = byte << tamanhoCodigoEmByte;
                fwrite(&byte, sizeof(char), 1, arqSaida);
                fseek(arqSaida, 0, SEEK_SET);
                fwrite(&tamanhoCodigoEmByte, sizeof(char), 1, arqSaida);
            }

            free(falta);
            fclose(arqSaida);
            fclose(arq);


        }
        else if(tipo == 'd')  // LORENNA EH COM VC
        {
            int lm;
            int posicao[];
            int letra[];
            while(fread(&aux, sizeof(char),1, arq)){
                criarArvoreD(letra, posicao);
                //pegar o caracter e transformar em número
                //ler a letra e o número e montar a árvore

            }
            /*
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
            fclose(arq);

            while(tamanho >= 2)
            {
                criarArvore(f);
            }*/
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
        }
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
