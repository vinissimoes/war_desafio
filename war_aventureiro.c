#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// struct igual ao nivel novato
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// função para cadastrar os territorios
void cadastrar(struct Territorio *mapa, int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do territorio %d ---\n", i+1);

        printf("Nome: ");
        fflush(stdin);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fflush(stdin);
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

// mostrar todos
void mostrar(struct Territorio *mapa, int qtd) {
    int i;
    printf("\n===== LISTA DOS TERRITORIOS =====\n");
    for (i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i+1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// função ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor) {

    int dadoA = (rand() % 6) + 1; 
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque acontecendo...\n");
    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoA);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("\nAtacante venceu!\n");

        // defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // metade das tropas do atacante vão para o defensor
        defensor->tropas = atacante->tropas / 2;

        printf("O territorio %s agora pertence ao exercito %s!\n",
               defensor->nome, defensor->cor);
    } 
    else {
        printf("\nDefensor venceu!\n");

        // atacante perde 1 tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }

        printf("O atacante perdeu 1 tropa.\n");
    }
}

// liberar memória
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

int main() {

    srand(time(NULL)); // para aleatoriedade funcionar

    int qtd, op;
    int at, def;

    struct Territorio *mapa;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar();

    // alocação dinâmica
    mapa = (struct Territorio*) malloc(qtd * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    cadastrar(mapa, qtd);

    do {
        printf("\n==== MENU AVENTUREIRO ====\n");
        printf("1 - Mostrar territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        if (op == 1) {
            mostrar(mapa, qtd);
        }
        else if (op == 2) {
            mostrar(mapa, qtd);

            printf("\nEscolha o numero do territorio atacante: ");
            scanf("%d", &at);
            getchar();

            printf("Escolha o numero do territorio defensor: ");
            scanf("%d", &def);
            getchar();

            // validacoes simples
            if (at == def) {
                printf("Erro: nao pode atacar o mesmo territorio.\n");
            }
            else if (strcmp(mapa[at-1].cor, mapa[def-1].cor) == 0) {
                printf("Erro: nao pode atacar um territorio da mesma cor.\n");
            }
            else {
                atacar(&mapa[at-1], &mapa[def-1]);
            }
        }

    } while (op != 0);

    liberarMemoria(mapa);

    return 0;
}
