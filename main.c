/*                                                  Projeto: 
                                    Sistema de cadastro de passagens aéreas.
                    
                            Integrantes:- Camila Piscioneri Magalhães, N°USP: 15697249;
                                        - Matheus Guilherme Ferreira Mendonça Learte, N°USP: 15522362.
                                
                            Obs: Por favor desconsiderar o outro trabalho enviado com a nossa participação. 

-------------------------------------------------------------------------------------------------------------------------------*/

// Bibliotecas utilizadas:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structs necessárias durante a execução do programa:
// Utilizada na função de Abertura de Voo:
typedef struct{
    int assentos;
    float executiva;
    float economica;
} Abertura;

// Utilizada na maioria das outras funções: 
typedef struct{
    char nome[50];
    char sobrenome[50];
    char cpf[15];
    int dia;
    int mes;
    int ano;
    char idvoo[5];
    char assento[4];
    char classe[10];
    float valor;
    char origem[4];
    char destino[4];
} Dados;

// indice das funções:
void ErroAlocar();
Abertura AV();
void ErroArquivo();
void LerArquivo(Dados **cadastro, int *qtdReservas, FILE *arquivo);
void FV(Dados **cadastro, int qtdReservas, FILE *arquivo, Abertura abertura);
Dados *RR();
void FD(int qtdReservas, Dados **cadastro, FILE *arquivo, Abertura abertura);
void CR(int qtdReservas, Dados **cadastro);
void MR(Dados **cadastro, int qtdReservas);
void CA(Dados **cadastro, int *qtdReservas);

// Função para caso haja algum erro de alocação.
void ErroAlocar(){
    printf("Erro ao alocar memoria\n");
    exit(1);
}

// Prepara o programa para a realização de reservas, realizando a coleta de informações sobre capacidade da aeronave e preços de classes de reserva. Essa função é realizada apenas uma única vez, independente da quantidade de fechamentos de dia efetuadas..
Abertura AV(){
    Abertura abertura;

    scanf("%d %f %f", &abertura.assentos, &abertura.economica, &abertura.executiva);

    return abertura;
}

// Função para caso haja algum erro na abertura no arquivo.
void ErroArquivo(){
    printf("Erro com o arquivo\n");
    exit(1);
}

// Função que, quando o programa é religado, devolve para as structs os cadastros que foram salvos nos arquivo.
void LerArquivo(Dados **cadastro, int *qtdReservas, FILE *arquivo){
    Dados cadastro_aux;

    while (fread(&cadastro_aux, sizeof(Dados), 1, arquivo) == 1){
        cadastro = (Dados **)realloc(cadastro, sizeof(Dados *) * (*qtdReservas + 1));
        cadastro[*qtdReservas] = (Dados *)malloc(sizeof(Dados));
        *cadastro[*qtdReservas] = cadastro_aux;
        (*qtdReservas)++;
    }

    return;
}

// Realiza o fechamento do voo, guarda os cadastros realizados no arquivo, informa que o Voo fechou e imprime o cpf, nome, sobrenome e o assento de todos os passageiros. Além disso a função imprime o valor total do Voo.
void FV(Dados **cadastro, int qtdReservas, FILE *arquivo, Abertura abertura){
    fwrite(&abertura, sizeof(Abertura), 1, arquivo);

    for (int i = 0; i < qtdReservas; i++){
        fwrite(cadastro[i], sizeof(Dados), 1, arquivo);
    }

    fclose(arquivo);

    printf("Voo Fechado!\n\n");

    for (int i = 0; i < qtdReservas; i++){
        printf("%s\n", cadastro[i]->cpf);
        printf("%s %s\n", cadastro[i]->nome, cadastro[i]->sobrenome);
        printf("%s\n\n", cadastro[i]->assento);
    }

    float valor_total = 0;
    for (int k = 0; k < qtdReservas; k++){
        valor_total += cadastro[k]->valor;
    }

    printf("Valor Total: %.2f\n", valor_total);

    for (int j = 0; j < 50; j++){
        printf("-");
    }

    for (int h = 0; h < qtdReservas; h++){
        free(cadastro[h]);
    }
    free(cadastro);

    return;
}

Dados *RR(){
    Dados *novaReserva = (Dados *)malloc(sizeof(Dados) * 1);

    scanf(" %s", novaReserva->nome);
    scanf(" %s", novaReserva->sobrenome);
    scanf(" %s", novaReserva->cpf);
    scanf(" %d", &novaReserva->dia);
    scanf(" %d", &novaReserva->mes);
    scanf(" %d", &novaReserva->ano);
    scanf(" %s", novaReserva->idvoo);
    scanf(" %s", novaReserva->assento);
    scanf(" %s", novaReserva->classe);
    scanf(" %f", &novaReserva->valor);
    scanf(" %s", novaReserva->origem);
    scanf(" %s", novaReserva->destino);

    return novaReserva;
}

void FD(int qtdReservas, Dados **cadastro, FILE *arquivo, Abertura abertura){
    fwrite(&abertura, sizeof(Abertura), 1, arquivo);

    for (int i = 0; i < qtdReservas; i++){
        fwrite(cadastro[i], sizeof(Dados), 1, arquivo);
    }

    fclose(arquivo);

    printf("Fechamento do dia:\n");

    printf("Quantidade de reservas: %d\n", qtdReservas);

    float valor_parcial = 0;
    for (int i = 0; i < qtdReservas; i++){
        valor_parcial += (*cadastro[i]).valor;
    }

    printf("Posição: %.2f", valor_parcial);

    for (int h = 0; h < qtdReservas; h++){
        free(cadastro[h]);
    }
    free(cadastro);

    return;
}

void CR(int qtdReservas, Dados **cadastro){
    char cpf[15];

    scanf(" %s", cpf);

    for (int i = 0; i < qtdReservas; i++){
        if (!strcmp(cpf, cadastro[i]->cpf)){
            printf("%s\n", cadastro[i]->cpf);
            printf("%s %s\n", cadastro[i]->nome, cadastro[i]->sobrenome);
            printf("%d/%d/%d\n", cadastro[i]->dia, cadastro[i]->mes, cadastro[i]->ano);
            printf("Voo: %s\n", cadastro[i]->idvoo);
            printf("Assento: %s\n", cadastro[i]->assento);
            printf("Classe: %s\n", cadastro[i]->classe);
            printf("Trecho: %s %s\n", cadastro[i]->origem, cadastro[i]->destino);
            printf("Valor %.2f\n", cadastro[i]->valor);

            for (int j = 0; j < 50; j++){
                printf("-");
            }
            printf("\n");
            break;
        }
    }

    return;
}

void MR(Dados **cadastro, int qtdReservas){
    char cpf[15];

    Dados aux;

    scanf(" %s %s %s %s %s", cpf, aux.nome, aux.sobrenome, aux.cpf, aux.assento);

    for (int i = 0; i < qtdReservas; i++){
        if (!strcmp(cpf, cadastro[i]->cpf)){
            strcpy(cadastro[i]->nome, aux.nome);
            strcpy(cadastro[i]->sobrenome, aux.sobrenome);
            strcpy(cadastro[i]->cpf, aux.cpf);
            strcpy(cadastro[i]->assento, aux.assento);

            printf("Reserva Modificada:\n");
            printf("%s\n", cadastro[i]->cpf);
            printf("%s %s\n", cadastro[i]->nome, cadastro[i]->sobrenome);
            printf("%d/%d/%d\n", cadastro[i]->dia, cadastro[i]->mes, cadastro[i]->ano);
            printf("Voo: %s\n", cadastro[i]->idvoo);
            printf("Assento: %s\n", cadastro[i]->assento);
            printf("Classe: %s\n", cadastro[i]->classe);
            printf("Trecho: %s %s\n", cadastro[i]->origem, cadastro[i]->destino);
            printf("Valor %.2f\n", cadastro[i]->valor);

            for (int j = 0; j < 50; j++){
                printf("-");
            }

            printf("\n");
            break;
        }
    }

    return;
}

void CA(Dados **cadastro, int *qtdReservas){
    char cpf[15];

    scanf(" %s", cpf);

    for (int i = 0; i < *qtdReservas; i++){
        if (!strcmp(cpf, cadastro[i]->cpf)){
            free(cadastro[i]);
            for (int j = i; j < *qtdReservas - 1; j++){
                cadastro[j] = cadastro[j + 1];
            }

            (*qtdReservas)--;

            break;
        }
    }

    return;
}

int main(void){
    int qtdReservas = 0;
    char comando[3];
    Dados **cadastro;
    cadastro = (Dados **)malloc(sizeof(Dados *) * 1);

    if (cadastro == NULL){
        ErroAlocar();
    }
    // Abro o arquivo para leitura
    FILE *arquivo;

    Abertura abertura;
    scanf(" %s", comando);

    if (!strcmp(comando, "AV")){
        abertura = AV();
    } else {
        arquivo = fopen("info_voo.txt", "rb");

        if (arquivo == NULL){
            ErroArquivo();
        }

        fread(&abertura, sizeof(Abertura), 1, arquivo);
        // Leio o arquivo
        LerArquivo(cadastro, &qtdReservas, arquivo);

        fclose(arquivo);
    }

    arquivo = fopen("info_voo.txt", "wb+");
    if (arquivo == NULL){
        ErroArquivo();
    }

    while (1){
        if (!strcmp(comando, "FV")){
            FV(cadastro, qtdReservas, arquivo, abertura);
            return 0;
        }

        if (!strcmp(comando, "RR")){
            if (qtdReservas == abertura.assentos){
                FV(cadastro, qtdReservas, arquivo, abertura);
                return 0;
            }

            cadastro = (Dados **)realloc(cadastro, sizeof(Dados *) * (qtdReservas + 1));
            cadastro[qtdReservas] = RR();
            qtdReservas++;
        }

        if (!strcmp(comando, "FD")){
            FD(qtdReservas, cadastro, arquivo, abertura);
            return 0;
        }

        if (!strcmp(comando, "CR")){
            CR(qtdReservas, cadastro);
        }

        if (!strcmp(comando, "MR")){
            MR(cadastro, qtdReservas);
        }

        if (!strcmp(comando, "CA")){
            CA(cadastro, &qtdReservas);
        }

        scanf(" %s", comando);
    }

    return 0;
}
