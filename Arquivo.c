#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <string.h>
#include <math.h>

/*
@author Lorenna Nunes e Maria Eduarda Elias Rocha
@since 2019.
*/

FILE *arq;
FILE *arqSaida;
Tabela* codigos;
Tabela* inicio;
NoArvore* auxCodigo;
int *frequencias;
long int tamanho;
int quantosBytes;
unsigned char *vetorDeLetras;

void criarArvore(NoFila* f)
{
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->esq = pop(f);
    novoNo->dir = pop(f);
    novoNo->vazio = 1;
    novoNo->freq = novoNo->esq->freq + novoNo->dir->freq;
    novoNo->letra = NULL;
    push(&f, novoNo);
    free(novoNo);
    tamanho = tamanho - 1;
}
void percorrerFila(NoFila *f)
{
    int k = 1;
    NoFila* n = f; //criar o n � necess�rio?
    while(n != NULL)
    {
        fwrite(&n->dado->letra, sizeof(char), 1, arqSaida);
        unsigned char byte1 = (n->dado->freq & 255);
        unsigned char byte2 = ((n->dado->freq>>8) & 255);
        unsigned char byte3 = ((n->dado->freq>>16) & 255);
        unsigned char byte4 = ((n->dado->freq>>24) & 255);
        fwrite(&byte1, sizeof(char), 1, arqSaida);
        fwrite(&byte2, sizeof(char), 1, arqSaida);
        fwrite(&byte3, sizeof(char), 1, arqSaida);
        fwrite(&byte4, sizeof(char), 1, arqSaida);
        k = k +1;
        n = n->prox;
    }
}

void lerArq(char *nome, char tipo)
{
    quantosBytes= 0;
    //se o arquivo aberto para leitura estiver nulo
    if( (arq = fopen(nome, "rb")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo, verifique sua existencia e o caminho");
    }
    else
    {
        fseek(arq, 0, SEEK_END);
        int size= ftell(arq);
        if(size == 0)
        {
             printf("Arquivo vazio!");
             return;
        }
        rewind(arq);
        tamanho = 0;
        int i = 0;
        int dados = 0;
        unsigned char aux;
        vetorDeLetras = (unsigned char*)malloc(257*sizeof(char));
        frequencias = (int*)malloc(257*sizeof(int));

        //se o usuario escolher a op��o de compactar
        if(tipo == 'c')
        {
            NoFila* f = create();
            char achou;
            printf("Compactando!\n");
            //enquanto consegue-se ler um char do arquivo
            while(fread(&aux, sizeof(char), 1, arq))
            {
                quantosBytes = quantosBytes +1;
                achou = 0;
                if(tamanho == 0)
                {
                    //vetor recebe a letra correspondente ao char lido
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

            //come�a a compacta��o
            //reinicia o arquivo
            rewind(arq);
            quantosBytes = 0;
            arqSaida = fopen(strcat(nome, ".dao"),"wb");
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }

            printf("Compactando!\n");
            fwrite(" ", sizeof(char), 1, arqSaida);

            //transformando os int para char
            unsigned char byte1 = (tamanho & 255);
            unsigned char byte2 = ((tamanho>>8) & 255);
            unsigned char byte3 = ((tamanho>>16) & 255);
            unsigned char byte4 = ((tamanho>>24) & 255);

            fwrite(&byte1, sizeof(char), 1, arqSaida);
            fwrite(&byte2, sizeof(char), 1, arqSaida);
            fwrite(&byte3, sizeof(char), 1, arqSaida);
            fwrite(&byte4, sizeof(char), 1, arqSaida);
            int j = 0;

            //repeti��o para criar os n�s das �rvores
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

            printf("Compactando!\n");
            percorrerFila(f);

            printf("Compactando!\n");

            while(tamanho >= 2)
            {
                criarArvore(f);
            }

            printf("Compactando!\n");
            codigos = (Tabela*)malloc(tamanho*sizeof(Tabela));
            codigos->prox = NULL;
            codigos->primeiro = 1;
            codigos->letra = NULL;
            codigos->codigo = NULL;
            int topo = 0;
            char codigo[257];
            criarTabela(f->dado, codigo, topo);
            inicio = (Tabela*)malloc(tamanho*sizeof(Tabela));
            inicio->prox = codigos;
            inicio->letra = NULL;

            int tamanhoCodigoEmByte = 0;
            char* falta;
            int byte = 0;
            unsigned char aux;
            int codigoAtual = 0;
            inicio->codigo = NULL;

            while(fread(&aux, sizeof(char), 1, arq))
            {
                while(codigos->letra != aux && codigos != NULL)
                {
                    codigos = codigos->prox;
                }
                if(codigos->letra == aux)
                {
                    int i = 0;
                    for(;i<codigos->tamanho; i++)
                    {
                        if(codigos->codigo[i] == '1')
                            codigoAtual += pow(2,(codigos->tamanho-1 - i));
                    }

                    byte = byte << codigos->tamanho;
                    byte += codigoAtual;
                    codigoAtual = 0;
                    tamanhoCodigoEmByte += codigos->tamanho;
                    while(tamanhoCodigoEmByte >=8)
                    {
                        unsigned char byteEscrever = byte >> (tamanhoCodigoEmByte - 8);
                        fwrite(&byteEscrever, sizeof(char), 1, arqSaida);
                        byte = byte << sizeof(int) * 8 - tamanhoCodigoEmByte + 8;
                        byte = byte >> sizeof(int) * 8 - tamanhoCodigoEmByte + 8;
                        tamanhoCodigoEmByte = tamanhoCodigoEmByte - 8;
                    }

                    codigos = inicio->prox;
                }
            }
            if(tamanhoCodigoEmByte != 0)
            {
                byte = byte << 8 - tamanhoCodigoEmByte;
                fwrite(&byte, sizeof(char), 1, arqSaida);
                fseek(arqSaida, 0, SEEK_SET);
                int t = 8 - tamanhoCodigoEmByte;
                fwrite(&t, sizeof(char), 1, arqSaida);
            }
            free(falta);
            fclose(arqSaida);
            fclose(arq);
            free(f);
            printf("Arquivo compactado com sucesso!\n\n\n");
        }
        //se o usuario escolher a op��o de descompactar
        else if(tipo == 'd')
        {
            printf("Descompactando!\n");
            int freq = 0;
            unsigned char letra;
            char lixo = 0;
            int i=0;
            fseek(arq, 0, SEEK_END);
            long fim = ftell(arq);
            rewind(arq);
            fread(&lixo, sizeof(char),1, arq);
            fread(&tamanho, sizeof(int),1, arq);
            NoFila* f = create();
            for(;i<tamanho;i++){
                fread(&letra, sizeof(char),1, arq);
                fread(&freq, sizeof(int),1, arq);
                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                x->freq = (int)freq;
                x->letra = (unsigned char)letra;
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(&f, x);
                free(x);
            }
            i = 0;
            while(tamanho >= 2)
            {
                criarArvore(f);
            }
            char nome1[240];
            int tamanhoNome = strlen(nome);
            memset(nome1, '\0', sizeof(nome1));

            strncpy(nome1, nome, tamanhoNome-4);
            arqSaida = fopen(nome1,"wb");
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }
            auxCodigo = (NoArvore*)malloc(sizeof(NoArvore));
            auxCodigo = NULL;

            char qtd;
            int cont= 0;
            while(fread(&aux,sizeof(char),1,arq))
            {
                qtd = 8;
                if(ftell(arq) == fim)
                    qtd = 8 - lixo;
                escreverArqD(&aux, f->dado, qtd, fim);
            }
            fclose(arq);
            fclose(arqSaida);

            printf("Arquivo descompactado com sucesso!\n\n\n");
        }
    }
}

void escreverArqD(unsigned char *car, NoArvore *raiz, char qtd, int fim){
    unsigned char aux;
    int t = 7;
    NoArvore *no = (NoArvore*)malloc(sizeof(NoArvore));
    if(auxCodigo == NULL)
        no = raiz;
    else{
        no = auxCodigo;
        auxCodigo = NULL;
    }
    while(t != -1 && qtd > 0)
    {
        while(no->vazio && t >=0){
            aux = *car >> 7;
            *car = *car << 1;

            t--;
            if(aux==1){
                no = no->dir;
            }
            else if(aux==0){
                no = no->esq;
            }
        }
        if(t == -1 && no->dir != NULL || no->esq != NULL)
        {
            auxCodigo = no;
            break;
        }

        if(ftell(arq) == fim)
        {
            qtd -= 7-t;
        }

        fwrite(&(no->letra), sizeof(char), 1, arqSaida);
        no = raiz;
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
        for(; i < topo; i++)
        {
            codigoReal[i] = codigo[i];
        }

        Tabela* t = (Tabela*)malloc(sizeof(Tabela));
        t->codigo = codigoReal;
        t->letra =  a->letra;
        t->prox = NULL;
        t->tamanho = topo;
        t->primeiro = 0;

        if(ta->primeiro == 1)
        {
            ta->codigo = codigoReal;
            ta->letra = a->letra;
            ta->tamanho = topo;
            ta->prox = NULL;
            ta->primeiro = 0;
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
