#include <stdio.h>
#include "Fila.h"
FILE *arq;
unsigned char *vetorDeLetras;
int tamanho;
char codigos[256][256];
extern void lerArq(char *nome, char tipo);
extern void percorrerArvore(NoArvore* a);
extern void criarArvore(NoFila* f);
extern void criarTabela(NoArvore* a, char codigo[], int topo);
extern void criarArquivo(char* nome);

