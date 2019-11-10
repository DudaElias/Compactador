#include <stdio.h>
#include "../Arquivo.h"
#include "../Fila.h"
#include <locale.h>
int main()
{
    int escolha;// escolha do usuario
    char nome[241];//o tamanho maximo para caminho eh 240 caracteres
    setlocale (LC_ALL, ""); // deixa o console usar UTF-8

    //inicio do menu principal
    printf("Projeto Compactador em C\n");
    printf("Feito por Lorenna Nunes e Maria Eduarda Rocha\n");
    printf("---------------------------------------------\n\n");

    do // enquanto o usuario não selecionar algo diferente de 1 e 2 continua fazendo o menu no final
    { //  de cada compactação ou descompactação
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
                    lerArq(nome, 'c'); // o parametro c indica que é uma compactação
                    break;
                case 2:
                    printf("Digite o caminho do arquivo: ");
                    scanf("%s" , &nome);
                    lerArq(nome, 'd');// o parametro d indica que é uma descompactação
                    break;
                default:
                    break;
            }
    }
    while(escolha != 3);
    return 0;
}
