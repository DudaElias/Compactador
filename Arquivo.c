#include "Arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include <string.h>
#include <math.h>

/*
@author Lorenna Nunes e Maria Eduarda Elias Rocha
@since 2019.
*/

FILE *arq;                   // arquivo de entrada
FILE *arqSaida;              // arquivo de saida
Tabela* codigos;             // Tabela dos códigos para a compactação
Tabela* inicio;              // Inicio da tabela de códigos para a compactação
NoArvore* auxCodigo;         // Auxiliar para a descompactação de arquivo, caso o byte tenha acabado e ainda falta
                             // percorrer um pedaço da arvore para chegar na folha onde parou no percurso da arvore é
                             // armazenado nessa variavel
int *frequencias;            // vetor de controle de frequencias do caracter no arquivo original
int tamanho;                 // quantos caracteres diferentes tem o arquivo
unsigned char *vetorDeLetras;// vetor que caminha junto com frequencias mas dessa vez como o caracter que tem aquela frequencia


void criarArvore(Fila* f) //cria a arvore tanto na compactação quanto na descompatação
{
    NoArvore* inserido; // no a ser inserido com a união dos dois primeiros da fila
    while(f->primeiro->prox != NULL) // enquanto existirem mais de 1 dado na fila
    {
        inserido = (NoArvore*)malloc(sizeof(NoArvore));
        inserido->esq = pop(f);
        inserido->dir = pop(f);
        inserido->letra = 0;
        inserido->vazio = 1; //coloca aquele no como vazio, variavel de controle para saber se eh folha ou n
        inserido->freq = inserido->esq->freq + inserido->dir->freq; // soma das frequencias
        push(&f, inserido); // insere o dado em ordem na fila
    }
}

void percorrerFila(NoFila *f) // percorre a fila para inserir ela no arquivo compactado
{
    NoFila* n = f;
    while(n != NULL)
    {
        fwrite(&n->dado->letra, sizeof(char), 1, arqSaida); // imprime o caracter
        unsigned char byte1 = (n->dado->freq & 255); // divide o inteiro de frequencia em 4 char para o arquivo,
        unsigned char byte2 = ((n->dado->freq>>8) & 255); // fwrite de inteiro trazia problemas de inversão de dados
        unsigned char byte3 = ((n->dado->freq>>16) & 255);
        unsigned char byte4 = ((n->dado->freq>>24) & 255);
        fwrite(&byte1, sizeof(char), 1, arqSaida);
        fwrite(&byte2, sizeof(char), 1, arqSaida);
        fwrite(&byte3, sizeof(char), 1, arqSaida);
        fwrite(&byte4, sizeof(char), 1, arqSaida);
        n = n->prox;
    }
}

void lerArq(char *nome, char tipo)
{
    //se o arquivo aberto para leitura estiver nulo
    if( (arq = fopen(nome, "rb+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo, verifique sua existencia e o caminho");
    }
    else
    {

        //Verifica se o arquivo está vazio, caso esteja, avisa o usuario e finaliza o programa
        fseek(arq, 0, SEEK_END);
        int size= ftell(arq);
        if(size == 0)
        {
             printf("Arquivo vazio!");
             return;
        }
        rewind(arq); // volta o ponteiro de percurso para o inicio do arquivo
        tamanho = 0;
        int i = 0;
        int dados = 0;
        unsigned char aux; // variavel que auxilia na compactacao e descompactacao para ler o arquivo original
        vetorDeLetras = (unsigned char*)malloc(257*sizeof(char)); // aloca 257 posicoes ao vetor de letras
        frequencias = (int*)malloc(257*sizeof(int));// aloca 257 posicoes ao vetor de frequencias

        //se o usuario escolher a opção de compactar
        if(tipo == 'c')
        {
            Fila* fila = NULL;
            create(&fila); // cria a fila
            char achou;
            printf("Compactando!\n");
            //enquanto consegue-se ler um byte do arquivo
            while(fread(&aux, sizeof(char), 1, arq)) // enquanto existir coisas no arquivo original será lido
            {                                        //e inserido no vetor de frequencias e de letras
                achou = 0;
                if(tamanho == 0)
                {
                    //vetor recebe a letra correspondente ao byte lido
                    vetorDeLetras[tamanho] = aux;
                    frequencias[tamanho] = 1;
                    tamanho++;
                }
                else
                {
                    for(;i<tamanho;i++)
                    {
                        if(vetorDeLetras[i] == aux)
                        {
                            frequencias[i]++;
                            achou = 1;
                        }
                    }
                    i = 0;
                    if(achou == 0)
                    {
                        vetorDeLetras[tamanho] = aux;
                        frequencias[tamanho] = 1;
                        tamanho++;
                    }
                }
            }

            //volta o ponteiro de percurso do arquivo para a posicao inicial
            rewind(arq);

            //INICIO DA COMPACTACAO
            arqSaida = fopen(strcat(nome, ".dao"),"wb"); //eh aberto um arquivo de saida que sera o nome do arquivo original mais a extensao dao
            if(arqSaida == NULL) // se o arquivo de saida for nulo significa que nao foi possivel inicia-lo
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }
            fwrite(" ", sizeof(char), 1, arqSaida); // espaco sera ocupado por bits de lixo ao final da compactacao
            unsigned char byte1 = (tamanho & 255); // separa o tamanho (que eh um int) em 4 bytes e escreve no arquivo compactado
            unsigned char byte2 = ((tamanho>>8) & 255);
            unsigned char byte3 = ((tamanho>>16) & 255);
            unsigned char byte4 = ((tamanho>>24) & 255);
            fwrite(&byte1, sizeof(char), 1, arqSaida);
            fwrite(&byte2, sizeof(char), 1, arqSaida);
            fwrite(&byte3, sizeof(char), 1, arqSaida);
            fwrite(&byte4, sizeof(char), 1, arqSaida);
            int j = 0;

            for(;j < tamanho;j++) // aqui ocorre a montagem da fila propriamente dita, usando o vetor de letras e frequencias
            {
                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                x->freq = (int)frequencias[j];
                x->letra = (unsigned char)vetorDeLetras[j];
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(&fila, x);
            }
            j = 0;
            percorrerFila(fila->primeiro); // escrever a fila no arquivo compactado
            criarArvore(fila); // criacao da arvore a partir da fila
            codigos = (Tabela*)malloc(tamanho*sizeof(Tabela));
            codigos->prox = NULL;
            codigos->primeiro = 1;
            codigos->letra = NULL;
            codigos->codigo = NULL;
            int topo = 0;
            char codigo[257];
            criarTabela(fila->primeiro->dado, codigo, topo); //monta a tabela de codigos para a compactacao
            inicio = (Tabela*)malloc(tamanho*sizeof(Tabela));
            inicio->prox = codigos;
            inicio->letra = NULL;

            int tamanhoCodigoEmByte = 0; // variavel de controle para saber quantos bits existem no byte a ser inserido no arquivo compactado
            int byte = 0; //variavel que armazenara os codigos binarios como inteiros
            int codigoAtual = 0; // variavel que recebera o valor do codigo binario para decimal
            inicio->codigo = NULL;

            while(fread(&aux, sizeof(char), 1, arq)) // enquanto puder ler o arquivo original para a compactacao
            {
                while(codigos->letra != aux && codigos != NULL) // percorre ate achar o codigo daquele caracter
                {
                    codigos = codigos->prox;
                }
                if(codigos->letra == aux)
                {
                    int i = 0;
                    for(;i<codigos->tamanho; i++) // transforma o codigo em inteiro
                    {
                        if(codigos->codigo[i] == '1')
                            codigoAtual += pow(2,(codigos->tamanho-1 - i));
                    }

                    byte = byte << codigos->tamanho; // byte "caminha" o tamanho do codigo a ser inserido para a esquerda
                    byte += codigoAtual; // byte recebe o codigo a ser inserido
                    codigoAtual = 0;
                    tamanhoCodigoEmByte += codigos->tamanho; // aumenta o tamanho da variavel de controle como o tamanho do codigo que foi inserido
                    while(tamanhoCodigoEmByte >=8) // enquanto já tiver bytes completos para ser inseridos no arquivo
                    {
                        unsigned char byteEscrever = byte >> (tamanhoCodigoEmByte - 8); // byteEscrever recebe os 8 primeiros bits de byte
                        fwrite(&byteEscrever, sizeof(char), 1, arqSaida); // escreve o byte no arquivo compactado
                        byte = byte << sizeof(int) * 8 - tamanhoCodigoEmByte + 8; //retira o byte escrito de byte
                        byte = byte >> sizeof(int) * 8 - tamanhoCodigoEmByte + 8; // volta byte para a posicao anterior, agora sem os bits retirados
                        tamanhoCodigoEmByte = tamanhoCodigoEmByte - 8; // reduz 8 no tamanho de codigos a inserir
                    }

                    codigos = inicio->prox; // volta codigos para o inicio
                }
            }
            if(tamanhoCodigoEmByte != 0) // caso tenha acabado a leitura do arquivoe ainda exista coisas a serem inseridas
            {
                byte = byte << 8 - tamanhoCodigoEmByte; // byte "andara" o que falta para completar um byte para a esquerda
                fwrite(&byte, sizeof(char), 1, arqSaida); // sera escrito o byte final
                fseek(arqSaida, 0, SEEK_SET); // volta o arquivo para o inicio
                int t = 8 - tamanhoCodigoEmByte; // calcula o numero de bits lixo
                fwrite(&t, sizeof(char), 1, arqSaida);//substitui o espaco pela quantidade de bits lixo
            }
            fclose(arqSaida); // fecha arquivos
            fclose(arq);
            free(fila);
            printf("Arquivo compactado com sucesso!\n\n\n");
        }
        //se o usuario escolher a opção de descompactar
        else if(tipo == 'd')
        {
            printf("Descompactando!\n");
            int freq = 0;
            unsigned char letra;
            char lixo = 0;
            int i=0;
            fseek(arq, 0, SEEK_END); // vai ate o final do arquivo para saber quando chegou ao byte final na descompactacao
            long int fim = ftell(arq);
            rewind(arq);
            fread(&lixo, sizeof(char),1, arq); // le qts bits lixo
            fread(&tamanho, sizeof(int),1, arq);//le qts caracteres diferentes
            Fila* fila = NULL;
            create(&fila); //inicia fila

            for(;i<tamanho;i++){ // forma a fila usando a fila no arquivo de compactacao
                fread(&letra, sizeof(char),1, arq);
                fread(&freq, sizeof(int),1, arq);
                NoArvore *x = (NoArvore*)malloc(sizeof(NoArvore));
                x->freq = (int)freq;
                x->letra = (unsigned char)letra;
                x->dir = NULL;
                x->esq = NULL;
                x->vazio = 0;
                push(&fila, x);
            }

            i = 0;
            criarArvore(fila); // cria a arvore a partir da fila

            char nome1[240];
            int tamanhoNome = strlen(nome);
            memset(nome1, '\0', sizeof(nome1));

            strncpy(nome1, nome, tamanhoNome-4); // retira a extensao .dao
            arqSaida = fopen(nome1,"wb+"); // abre o arquivo para escrita do descompactado
            if(arqSaida == NULL)
            {
                printf("Erro na abertura do arquivo!");
                return 1;
            }
            auxCodigo = (NoArvore*)malloc(sizeof(NoArvore));
            auxCodigo = NULL;

            char qtd;
            int cont= 0;
            while(fread(&aux,sizeof(char),1,arq))
            {
                qtd = 8;
                if(ftell(arq) == fim) // se for o byte final qtd recebera somente o quanto do byte eh valido
                    qtd = 8 - lixo;
                escreverArqD(&aux, fila->primeiro->dado, qtd, fim); // acha os codigos e escreve no arquivo descompactado os caracteres corretos
            }
            fclose(arq); // fecha os arquivos
            fclose(arqSaida);

            printf("Arquivo descompactado com sucesso!\n\n\n");
        }
    }
}

void escreverArqD(unsigned char *car, NoArvore *raiz, char qtd, int fim){
    unsigned char aux;
    int t = 7;
    NoArvore *no = (NoArvore*)malloc(sizeof(NoArvore));
    if(auxCodigo == NULL) // se n tiver no meio do percurso no recebe raiz
        no = raiz;
    else{ // se estiver no recebe onde parou no percurso
        no = auxCodigo;
        auxCodigo = NULL;
    }
    while(t != -1 && qtd > 0) // enquanto n tiver percorrido todo o byte e qtd for maior que 0
    {
        while(no->vazio && t >=0){ // enquanto n for folha
            aux = *car >> 7; // pega um bit
            *car = *car << 1; // retira o bit

            t--;
            if(aux==1){ // se o bit lido for um, ir para direita
                no = no->dir;
            }
            else if(aux==0){ // se for 0 para a esquerda
                no = no->esq;
            }
        }
        if(t == -1 && no->dir != NULL || no->esq != NULL)// caso tenha acabado de ler o byte e n tiver chegado em uma folha auxCodigo recebe onde parou no percurso
        {
            auxCodigo = no;
            break;
        }

        if(ftell(arq) == fim) // se for o fim, ir decrescendo o qtd ate chegar em 0
        {
            qtd -= 7-t;
        }
        fwrite(&(no->letra), sizeof(char), 1, arqSaida); // escreve o caracter encontrado no arquivo descompactado
        no = raiz;
    }
}

void criarTabela(NoArvore* a, char codigo[], int topo) // cria a tabela de codigos
{
    int i;
    if(a->esq) // enquanto for possivel ir para a esquerda
    {
        codigo[topo] = '0'; // adicionar 0 ao topo do vetor de codigo
        criarTabela(a->esq, codigo, topo+1); // ir para a esquerda
    }
    if(a->dir) // enquanto for possivel ir para a direita
    {
        codigo[topo] = '1'; // adicionar 1 ao topo do vetor de codigo
        criarTabela(a->dir, codigo, topo+1);//ir para a direita
    }
    if(a->esq == NULL && a->dir == NULL) // se for folha
    {
        Tabela *ta = codigos;
        i = 0;
        char* codigoReal = (char*)malloc(topo * sizeof(char));
        for(; i < topo; i++) // retira o lixo do final do vetor de codigo encontrado
        {
            codigoReal[i] = codigo[i];
        }


        Tabela* t = (Tabela*)malloc(sizeof(Tabela)); // adiciona uma tabela
        t->codigo = codigoReal;
        t->letra =  a->letra;
        t->prox = NULL;
        t->tamanho = topo;
        t->primeiro = 0;

        if(ta->primeiro == 1) // caso tabela esteja vazio, adiciona o t como o primeiro
        {
            ta->codigo = codigoReal;
            ta->letra = a->letra;
            ta->tamanho = topo;
            ta->prox = NULL;
            ta->primeiro = 0;
        }
        else // caso n adiciona no fim da tabela de codigos
        {
            while(ta->prox != NULL)
            {
                ta = ta->prox;
            }
            t->prox = ta->prox;
            ta->prox = t;
        }
    }
}

