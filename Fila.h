#ifndef FILA
#define FILA

typedef struct NoArvore
{
    char letra;
    char vazio;
    int freq;
    struct NoArvore *esq, *dir;
}NoArvore;

typedef struct NoFila{
    NoArvore dado;
    NoArvore* prox;

}NoFila;


extern NoFila create();
extern void push(NoFila *f, NoFila *dado);
extern NoFila* pop(NoFila *f);

#endif
