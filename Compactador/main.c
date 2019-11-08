#include <stdio.h>
#include "../Arquivo.h"
#include "../Fila.h"
int main()
{
    int escolha;
    char nome[240];

    printf("Projeto Compactador em C\n");
    printf("Feito por Lorenna Nunes e Maria Eduarda Rocha\n");
    printf("---------------------------------------------\n\n");

    do
    {
        printf("Selecione uma das opções abaixo:\n");
        printf("1 - Compactar um arquivo\n");
        printf("2 - Descompactar um arquivo\n");
        printf("3 - Sair\n\n");
        printf("Escolha: ");

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
                default:
                    break;
            }
    }
    while(escolha != 3);
    return 0;
}
