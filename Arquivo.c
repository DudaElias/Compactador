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
NoArvore* auxCodigo;

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
    tamanho = tamanho - 1;
}

void criarArvoreD(NoFila* raiz){
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    novoNo->esq = pop(raiz);
    novoNo->dir = pop(raiz);
    novoNo->vazio = 1;
    novoNo->freq = novoNo->esq->freq + novoNo->dir->freq;
    novoNo->letra= NULL;
    push(&raiz, novoNo);
    free(novoNo);
    tamanho = tamanho - 1;
}
void percorrerFila(NoFila *f)
{
    NoFila* n = f;
    while(n != NULL)
    {
        //printf("%c\n", n->dado->letra);
        //printf("%d\n", n->dado->freq);
        putchar('\n');
        if(n->dado->letra != NULL)
        {
            fwrite(&n->dado->letra, sizeof(char), 1, arqSaida);
            unsigned char byte1 = (n->dado->freq & 255);
            unsigned char byte2 = ((n->dado->freq>>8) & 255);
            unsigned char byte3 = ((n->dado->freq>>16) & 255);
            unsigned char byte4 = ((n->dado->freq>>31) & 255);
            fwrite(&byte1, sizeof(char), 1, arqSaida);
            fwrite(&byte2, sizeof(char), 1, arqSaida);
            fwrite(&byte3, sizeof(char), 1, arqSaida);
            fwrite(&byte4, sizeof(char), 1, arqSaida);
        }
        n = n->prox;
    }
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
            arqSaida = fopen(strcat(nome, ".dao"),"wb");
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }
            fwrite(" ", sizeof(char), 1, arqSaida);
            fwrite(&tamanho, sizeof(char), 1, arqSaida);
            //printf("%d", tamanho);
            percorrerFila(f);
            while(tamanho >= 2)
            {
                criarArvore(f);
            }
            percorrerArvore(f->dado);
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
            unsigned char aux;
            int codigoAtual = 0;
            inicio->codigo = NULL;
            while(fread(&aux, sizeof(char), 1, arq))
            {
                while(codigos->letra != aux && codigos != NULL)
                    codigos = codigos->prox;
                if(codigos->letra == aux)
                {
                    int v;
                    if(tamanhoCodigoEmByte != 0)
                    {
                        int i = 0;
                        for(;i<codigos->tamanho; i++)//convertedo p int
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
                        else//  ERRO CUIDADO
                        {
                            byte = byte << tamanhoCodigoEmByte;
                            byte += codigoAtual >>(codigos->tamanho - tamanhoCodigoEmByte);
                            int t = codigos->tamanho - tamanhoCodigoEmByte;
                            fwrite(&byte, sizeof(char),1, arqSaida);
                            byte = 0;
                            //byte += codigoAtual << codigos->tamanho + tamanhoCodigoEmByte;
                            byte += codigoAtual << 8 - tamanhoCodigoEmByte;
                            byte = byte >> 8 - tamanhoCodigoEmByte;
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
            int freq = 0;
            unsigned char letra;
            char lixo = 0;
            int i=0;
            fseek(arq, 0, SEEK_END);
            long fim = ftell(arq);
            rewind(arq);
            fread(&lixo, sizeof(char),1, arq);
            fread(&tamanho, sizeof(char),1, arq);

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
            while(tamanho >= 2)
            {
                criarArvoreD(f);
            }
            percorrerArvoreD(f->dado);
             char nome1[240];
            int tamanhoNome = strlen(nome);
               memset(nome1, '\0', sizeof(nome1));

            strncpy(nome1, nome, tamanhoNome-4);
            printf("%s", nome1);
            arqSaida = fopen(nome1,"wb");
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }
            auxCodigo = (NoArvore*)malloc(sizeof(NoArvore));
            auxCodigo = NULL;

            char qtd;
            while(fread(&aux,sizeof(char),1,arq))
            {
                qtd = 8;
                printf("%d\n", aux);
                if(ftell(arq) == fim)
                    qtd = 8 - lixo;
                escreverArqD(&aux, f->dado, qtd, fim);
            }



            fclose(arq);
            fclose(arqSaida);
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
        while(no->dir != NULL && no->esq != NULL && t >=0){
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
        if(t == -1 && no->dir !=NULL || no->esq!= NULL)
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
        for(; i< topo; i++)
        {
            codigoReal[i] = codigo[i];
        }

        printf("%c\t", a->letra);
        printf("%s\n", codigoReal);


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
    if(a->letra != NULL)
    {
        /*fwrite(&a->letra, sizeof(char), 1, arqSaida);
        unsigned char byte1 = (a->freq & 255);
        unsigned char byte2 = ((a->freq>>8) & 255);
        unsigned char byte3 = ((a->freq>>16) & 255);
        unsigned char byte4 = ((a->freq>>31) & 255);
        fwrite(&byte1, sizeof(char), 1, arqSaida);
        fwrite(&byte2, sizeof(char), 1, arqSaida);
        fwrite(&byte3, sizeof(char), 1, arqSaida);
        fwrite(&byte4, sizeof(char), 1, arqSaida);*/
    }
    for(;j<4;j++)
    {
        v = a->freq >> j * 8;
        //fwrite(&v, sizeof(char),1, arqSaida);
    }
    printf("%c\t", a->letra);//quando eu uso o << ou +
    printf("%d\n", a->freq);
    percorrerArvore(a->dir);

}

void percorrerArvoreD(NoArvore* a)
{
    if(a == NULL)
        return;
    percorrerArvore(a->esq);
    Letra t;
    t.letra = a->letra;
    t.freq = a->freq;
    int j = 0;
    char v;
    for(;j<4;j++)
    {
        v = a->freq >> j * 8;
        //fwrite(&v, sizeof(char),1, arqSaida);
    }
    printf("%c\t", a->letra);//quando eu uso o << ou +
    printf("%d\n", a->freq);
    percorrerArvore(a->dir);

}
