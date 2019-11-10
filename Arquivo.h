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

extern void lerArq(char *nome, char tipo);
extern void escreverArqD(unsigned char *car, NoArvore *raiz, char qtd, int fim);
extern void percorrerFila(NoFila* f);
extern void criarArvore(Fila* f);
extern void criarTabela(NoArvore* a, char codigo[], int topo);

