/*                                                    Projeto: 
                                        Sistema de cadastro de passagens aéreas.
                    
                                Integrantes:- Camila Piscioneri Magalhães, N°USP: 15697249;
                                            - Matheus Guilherme Ferreira Mendonça Learte, N°USP: 15522362.
                                
                        Obs: Por favor desconsiderar o outro trabalho enviado com a nossa participação.

                                                    Objetivo:

                    Uma companhia área deseja informatizar seu sistema de reserva de passagens, e você e sua
                equipe serão os encarregados do projeto e desenvolvimento. Para esta versão inicial a companhia
                    espera um sistema simplificado, considerando uma única aeronave, que reserve apenas trecho de
                                voo simples (único trecho) e para um único passageiro por vez.

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
void ErroAlocar(); //Erro de alocação
Abertura AV(); // Abertura de Voo
void ErroArquivo(); //Erro na abertura de arquivo
void LerArquivo(Dados **cadastro, int *qtdReservas, FILE *arquivo); 
void FV(Dados **cadastro, int qtdReservas, FILE *arquivo, Abertura abertura); // Fechamento do Voo
Dados *RR(); // Realizar Reserva
void FD(int qtdReservas, Dados **cadastro, FILE *arquivo, Abertura abertura); // Fechamento do Dia
void CR(int qtdReservas, Dados **cadastro); // Consultar Reserva
void MR(Dados **cadastro, int qtdReservas); // Modificar Reserva
void CA(Dados **cadastro, int *qtdReservas); // Cancelar Reserva

// Função para caso haja algum erro de alocação de memória.
void ErroAlocar(){
    printf("Erro ao alocar memoria\n");
    exit(1);
}

// Prepara o programa para a realização de reservas, realizando a coleta de informações sobre capacidade da aeronave e preços de classes de reserva. Essa função é realizada apenas uma única vez, independente da quantidade de fechamentos de dia efetuadas.
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

// Função que tem como responsabilidade, quando o programa é religado, devolver para as structs os cadastros que foram salvos no arquivo antes do Fechamento do Dia (FD).
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

// Realiza o fechamento do voo guardando os cadastros realizados no arquivo, ela também informa que o Voo fechou e imprime o cpf, nome, sobrenome e o assento de todos os passageiros cadastrados. Além disso a função imprime o valor total obtido desde a Abertura do Voo (AV). Depois do comando FV não se pode mais fazer alterações no voo, ele fecha permamentemente com os dados inseridos até então.
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

// Adiciona uma nova reserva no voo. Ela declara um ponteiro (Dados *novaReserva) para armazenar esses dados inseridos (da struct com tipo Dados) pelo usuário e retorna para um vetor (cadastro[qtdReservas]) e um contador (int qtdReservas) na main.
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

// Tem como objetivo imprimir o número de reservas total que foram feitas até o momento em que a função foi chamada, guardar no arquivo as reservas feitas (para se poder utilizar essas informções depois do comando FD). Depois que a função termina o programa é fechado e ele pode ser iniciado novamente com todas as informações anteriormente inseridas antes de encerrar, ao contrário da função de Fechamento de Voo (FV) que fecha o voo permamentemente.
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

// Com o objetivo de consultar uma reserva posteriormente feita usando a função de Realizar Reserva (RR). A função usa como parametro o cpf utilizado na reserva e a partir daí busca no cadastro o cpf correspondente e logo em seguida imprime os principais dados daquela struct (cpf, nome completo, data, id do voo, assento, classe, valor, origem e destino).
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

// Função que modica a reverva de um passageiro. Ela procura no cadastro através de um cpf que foi informado com a sua chamada e logo em seguida faz a ateração que se foi passada também junto com a chamada (podem ser feitas alterações no nome, sobrenome, cpf ou/e assento) e depois imprime a reserva com as informações alteradas e não alteradas.
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

// Seu objetivo é apagar o cadastro de algum passageiro do sistema, ou seja, cancelar uma reserva. A função realiza essa ação pegando o cpf, que foi informado junto com sua chamada, depois procurando o cadastro no sistema e após ser encontrado ele é totalmente apagado e a quantidade de reservas (contador) também é diminuido.
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

// Função principal onde o arquivo é administrado, as principais variáveis que utilizamos no codigo estão declaradas e onde se há a chamada de cada função de acordo com o que foi digitado pelo usuário, para isso foi utilizado comandos de repetição e de seleção.
int main(void){
    int qtdReservas = 0;
    char comando[3];
    Dados **cadastro;
    cadastro = (Dados **)malloc(sizeof(Dados *) * 1);

    if (cadastro == NULL){
        ErroAlocar();
    }
    
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
