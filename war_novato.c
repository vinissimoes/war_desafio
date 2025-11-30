#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// struct para guardar dados dos territorios
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    struct Territorio t[QTD_TERRITORIOS]; // vetor
    int i;

    printf("Cadastro dos territorios\n");

    // loop para pegar os dados
    for(i = 0; i < QTD_TERRITORIOS; i++){
        printf("\nTerritorio %d\n", i+1);

        printf("Nome: ");
        fflush(stdin);
        fgets(t[i].nome, 30, stdin);
        t[i].nome[strcspn(t[i].nome, "\n")] = 0; // tirar enter

        printf("Cor do exercito: ");
        fflush(stdin);
        fgets(t[i].cor, 10, stdin);
        t[i].cor[strcspn(t[i].cor, "\n")] = 0;

        printf("Qtd tropas: ");
        scanf("%d", &t[i].tropas);

        getchar(); // limpar o enter perdido
    }

    // mostrar os dados cadastrados
    printf("\n--- Dados cadastrados ---\n");

    for(i = 0; i < QTD_TERRITORIOS; i++){
        printf("\nTerritorio %d:\n", i+1);
        printf("Nome: %s\n", t[i].nome);
        printf("Cor: %s\n", t[i].cor);
        printf("Tropas: %d\n", t[i].tropas);
    }

    return 0;
}
