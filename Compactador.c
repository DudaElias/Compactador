#include <stdio.h>
#include "Arquivo.c"
int main()
{
    int escolha;
    char nome[200];

    printf("Projeto Compactador em C\n");
    printf("Feito por Lorenna Nunes e Maria Eduarda Rocha\n");
    printf("---------------------------------------------\n\n");
    printf("Selecione uma das opções abaixo:\n");
    printf("1 - Compactar um arquivo\n");
    printf("2 - Descompactar um arquivo\n");
    printf("3 - Sair\n");

    scanf("%d", &escolha);

    switch(escolha)
    {
        case 1:
            printf("Digite o caminho do arquivo: ");
            scanf("%s" , &nome);
            lerArq(nome);
            break;
        case 2:
            printf("2");
            break;
        case 3:
            break;
    }
    return 0;
}
