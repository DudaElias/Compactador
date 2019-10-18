typedef struct NoArvore
{
    char letra;
    char vazio;
    int freq;
    struct NoArvore *esq, *dir;

}
NoArvore;

NoArvore *raiz, *atual, *ant;

extern void setEsq();
extern void setDir();
