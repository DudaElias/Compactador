#include "Arquivo.h"
#include <stdio.h>

FILE *arq;
void lerArq(char *nome)
{
    if(fopen(nome, "r") == NULL)
    {
        printf("Não foi possivel abrir o arquivo, verifique sua existência e o caminho");
    }
    else
    {

    }

}
