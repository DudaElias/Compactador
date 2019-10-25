#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Aluno{
    char nome[10];
    int idade;
}Aluno;

int main()
{
    FILE *fil;
    struct Aluno a;
    fil = fopen("a.txt", "wb");
    a.idade = 4;
    strcpy(a.nome, "Dudao");
    fwrite(&a, sizeof(struct Aluno), 1, fil);
    fclose(fil);
}
