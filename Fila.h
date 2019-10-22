#ifndef FILA
#define FILA

typedef struct NoArvore
{
    unsigned char letra;
    char vazio;
    int freq;
    struct NoArvore *esq, *dir;
}NoArvore;

typedef struct NoFila{
    NoArvore* dado;
    struct NoFila* prox;

}NoFila;


extern NoFila* create();
extern void push(NoFila **f, NoArvore *dado);
extern void percorrer(NoFila *f);
extern NoArvore* pop(NoFila *f);

#endif
