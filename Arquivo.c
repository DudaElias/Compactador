#include "Arquivo.h"
#include <stdio.h>

FILE *arq;
void lerArq(char *nome)
{
    if(fopen(nome, "r") == NULL)
    {
        printf("N�o foi possivel abrir o arquivo, verifique sua exist�ncia e o caminho");
    }
    else
    {

    }

}
