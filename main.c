#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    float executiva;
    float economica;
} Valor;

typedef struct{
    char *nome;
    char *sobrenome;
    char cpf[15];
    int dia;
    int mes;
    int ano;
    char *idvoo;
    char assento[4];
    char classe[10];
    float valor;
    char *origem;
    char *destino;
} Dados;

// Protótipo das Funções:
void *aloca(int N, int J); //*
void AV(int *assentos, Valor* valores); //*
void RR(Dados *cadastro, int cont); //*
void CR(int assentos, Dados *cadastro); //*
void MR(Dados *cadastro, int assentos); //*
void CA(Dados *cadastro, int assentos, Valor valores); //* (meio)
void FD(); //* (meio)
void FV(Dados *cadastro, int assentos); //* (meio) 

void *aloca(int N, int J){
    void *p = malloc(N * J);

    if (p == NULL){
        printf("Sem espaço");
        exit(1);
    }

    return (p);
}

void AV(int *assentos, Valor* valores){

    scanf("%d %f %f", assentos, &valores->executiva, &valores->economica);

    return;
}

void RR(Dados *cadastro, int cont) {
    char *p;

    p = (char*) aloca(sizeof(char), 300);
    scanf(" %299s", p);
    cadastro[cont].nome = (char*) aloca(sizeof(char), strlen(p) + 1);
    strcpy(cadastro[cont].nome, p);
    free(p);

    p = (char*) aloca(sizeof(char), 300);
    scanf(" %299s", p);
    cadastro[cont].sobrenome = (char*) aloca(sizeof(char), strlen(p) + 1);
    strcpy(cadastro[cont].sobrenome, p);
    free(p);

    scanf(" %14s", cadastro[cont].cpf);

    scanf("%d %d %d", &cadastro[cont].dia, &cadastro[cont].mes, &cadastro[cont].ano);

    p = (char*) aloca(sizeof(char), 5);
    scanf(" %4s", p);
    cadastro[cont].idvoo = (char*) aloca(sizeof(char), strlen(p) + 1);
    strcpy(cadastro[cont].idvoo, p);
    free(p);

    scanf(" %3s", cadastro[cont].assento);

    scanf(" %9s", cadastro[cont].classe);

    scanf("%f", &cadastro[cont].valor);

    p = (char*) aloca(sizeof(char), 500);
    scanf(" %499s", p);
    cadastro[cont].origem = (char*) aloca(sizeof(char), strlen(p) + 1);
    strcpy(cadastro[cont].origem, p);
    free(p);

    p = (char*) aloca(sizeof(char), 500);
    scanf(" %499s", p);
    cadastro[cont].destino = (char*) aloca(sizeof(char), strlen(p) + 1);
    strcpy(cadastro[cont].destino, p);
    free(p);
}

void CR(int assentos, Dados *cadastro) {
    char cpf[15];

    scanf("%s", cpf);

    printf("\n");

    for (int i = 0; i < assentos; i++) {
        if (strcmp(cpf, cadastro[i].cpf) == 0) {
            printf("%s\n", cadastro[i].cpf);
            printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
            printf("%d/%d/%d\n", cadastro[i].dia, cadastro[i].mes, cadastro[i].ano);
            printf("Voo: %s\n", cadastro[i].idvoo);
            printf("Assento: %s\n", cadastro[i].assento);
            printf("Classe: %s\n", cadastro[i].classe);
            printf("Trecho: %s %s\n", cadastro[i].origem, cadastro[i].destino);
            printf("Valor %.2f\n", cadastro[i].valor);

            for (int j = 0; j < 50; j++) {
                printf("-");
            }
            printf("\n");
            break;
        }
    }
}

void MR(Dados *cadastro, int assentos){ 
    char cpf[15];
    int encontrado = 0;

    scanf(" %s", cpf);

    for (int i = 0; i < assentos; i++){
        if (strcmp(cpf, cadastro[i].cpf) == 0){
            
            scanf(" %s %s %s %s", cadastro[i].nome, cadastro[i].sobrenome, cadastro[i].cpf, cadastro[i].assento);
            encontrado = 1;

            printf("Reserva Modificada:\n");
            printf("%s\n", cadastro[i].cpf);
            printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
            printf("%d/%d/%d\n", cadastro[i].dia, cadastro[i].mes, cadastro[i].ano);
            printf("Voo: %s\n", cadastro[i].idvoo);

            for (int j = 0; j < 50; j++){
                printf("-");
            }

            printf("\n");
            break;
        }
    }

    if (!encontrado){
        printf("Reserva não encontrada.\n");
    }
}

void CA(Dados *cadastro, int assentos, Valor valores){ 
    char cpf[15];
    int encontrado = 0;

    scanf("%s", cpf);

    for (int i = 0; i < assentos; i++){
        if (strcmp(cpf, cadastro[i].cpf) == 0){

            encontrado = 1;

            strcpy(cadastro[i].cpf, "");

            free(cadastro[i].nome);
            cadastro[i].nome = NULL;

            free(cadastro[i].sobrenome);
            cadastro[i].sobrenome = NULL;

            cadastro[i].dia = 0;
            cadastro[i].mes = 0;
            cadastro[i].ano = 0;

            strcpy(cadastro[i].idvoo, "");
            strcpy(cadastro[i].assento, "");
            strcpy(cadastro[i].classe, "");
            cadastro[i].valor = 0.0;

            strcpy(cadastro[i].origem, "");
            strcpy(cadastro[i].destino, "");

            break;
        }
    }

    if (!encontrado){
        printf("Reserva não encontrada.\n");
    }
}

void FD(int* cont, Valor *cadastro){ 
    int valor_parcial = 0.0;
    printf("Fechamento do dia:\n");
    
    printf("Quantidade de reservas: %d", *cont);

    for(int i=0; i<cont; i++){
        valor_parcial += cadastro[i].valor;
    }

    printf("Posição: %.2f", valor_parcial);

}

void FV(Dados *cadastro, int assentos){ //imprimir todo o arquivo
    FILE *arquivo = fopen("info_voo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    
    printf("Voo Fechado!\n");

    for (int i = 0; i < assentos; i++){

        printf("\n%s\n", cadastro[i].cpf);
        printf("%s %s\n", cadastro[i].nome, cadastro[i].sobrenome);
        printf("%s\n", cadastro[i].assento);
    }

    float valor_total = 0;
    for (int k = 0; k < assentos; k++){
        valor_total += cadastro[k].valor;
    }

    printf("\nValor Total: %f\n", valor_total);

    for (int j = 0; j < 50; j++){
        printf("-");
    }

    for (int h = 0; h < assentos; h++){

        free(cadastro[h].nome);
        cadastro[h].nome = NULL;

        free(cadastro[h].sobrenome);
        cadastro[h].sobrenome = NULL;

        strcpy(cadastro[h].cpf, "");

        cadastro[h].dia = 0;
        cadastro[h].mes = 0;
        cadastro[h].ano = 0;

        strcpy(cadastro[h].idvoo, "");
        strcpy(cadastro[h].assento, "");
        strcpy(cadastro[h].classe, "");
        cadastro[h].valor = 0.0;

        strcpy(cadastro[h].origem, "");
        strcpy(cadastro[h].destino, "");
    }
    free(cadastro);
}

int main(void){
    char comando[3];
    int assentos;
    Valor valores;
    Dados *cadastro;
    int cont = 0;

    scanf("%s", comando);

    if(strcmp(comando, "AV")==0){

        AV(&assentos, &valores);
    }

    do{
        scanf("%s", comando);
        
        if (strcmp(comando, "RR") == 0){
            cadastro = (Dados *)aloca(sizeof(Dados), assentos);
            RR(cadastro, cont);
            cont++;
        }

        if (strcmp(comando, "CR") == 0){
            CR(assentos, cadastro);
        }

        if (strcmp(comando, "MR") == 0){
            MR(cadastro, assentos);
        }

        if (strcmp(comando, "CA") == 0){
            CA(cadastro, assentos,  valores);
        }

    } while (strcmp(comando, "FD") != 0 || strcmp(comando, "FV") != 0 || cont < assentos);
    if(cont==assentos){
        printf("Voo Fechado!");
    }else
    if (strcmp(comando, "FV") == 0 || cont >= assentos){
        FV(cadastro, assentos);
    } else if (strcmp(comando, "FD") == 0){
        FD(&cont, &cadastro);
    }

    return 0;
}