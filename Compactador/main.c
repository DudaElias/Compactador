#include <stdio.h>
#include "../Arquivo.h"
#include "../Fila.h"
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
            fflush(stdin);
            lerArq(nome, 'c');
            break;
        case 2:
            printf("Digite o caminho do arquivo: ");
            scanf("%s" , &nome);
            fflush(stdin);
            lerArq(nome, 'd');
            break;
            break;
    }
    return 0;
}
