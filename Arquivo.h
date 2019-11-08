#include <stdio.h>
#include "Fila.h"

typedef struct Tabela{
    unsigned char letra;
    char* codigo;
    int tamanho;
    char primeiro;
    struct Tabela* prox;
    //ponteiro do ponteiro
}Tabela;

typedef struct Letra{

    unsigned char letra;
    int freq;
}Letra;

FILE *arq;
unsigned char *vetorDeLetras;
long int tamanho;
Tabela *codigos;
int quantosBytes;
extern void lerArq(char *nome, char tipo);
extern void escreverArqD(unsigned char *car, NoArvore *raiz, char qtd, int fim);
extern void percorrerArvore(NoArvore* a);
extern void percorrerFila(NoFila* f);
extern void criarArvore(NoFila* f);
extern void criarTabela(NoArvore* a, char codigo[], int topo);
extern void criarArquivo(char* nome);

