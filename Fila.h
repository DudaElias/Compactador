#ifndef FILA
#define FILA

typedef struct NoArvore
{
    unsigned char letra;
    char vazio;
    int freq;
    struct NoArvore *esq, *dir;
}NoArvore;



typedef struct Fila{
    struct NoFila* primeiro;
}Fila;


typedef struct NoFila{
    NoArvore* dado;
    struct NoFila* prox;

}NoFila;


extern void create(Fila**f);
extern void push(Fila **f, NoArvore *dado);
extern void percorrer(NoFila *f);
extern NoArvore* pop(Fila *f);

#endif
