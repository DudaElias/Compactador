#include <stdio.h>
#include "Fila.h"

typedef struct Tabela{
    unsigned char letra;
    char* codigo;
    struct Tabela* prox;
    //ponteiro do ponteiro
}Tabela;

typedef struct Letra{

    unsigned char letra;
    int freq;
}Letra;

FILE *arq;
unsigned char *vetorDeLetras;
int tamanho;
Tabela *codigos;
extern void lerArq(char *nome, char tipo);
extern void percorrerArvore(NoArvore* a);
extern void criarArvore(NoFila* f);
extern void criarTabela(NoArvore* a, char codigo[], int topo);
extern void criarArquivo(char* nome);

