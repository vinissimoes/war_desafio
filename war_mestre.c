#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR  15

// struct para representar um territorio
struct Territorio {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
};

// atribui/ler territorios dinamicamente
void cadastrar(struct Territorio *mapa, int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do territorio %d ---\n", i + 1);

        printf("Nome: ");
        fflush(stdin);
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exercito (ex: vermelho, azul): ");
        fflush(stdin);
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

// mostrar mapa
void exibirMapa(struct Territorio *mapa, int qtd) {
    int i;
    printf("\n===== MAPA =====\n");
    for (i = 0; i < qtd; i++) {
        printf("%d) %s | Cor: %s | Tropas: %d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// atacar: usa ponteiros para modificar territorios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nRolagem: Atacante %s -> %d | Defensor %s -> %d\n",
           atacante->nome, dadoA, defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");
        // defensor muda de dono e ganha metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 0) defensor->tropas = 0;
        printf("%s agora e do exercito %s com %d tropas.\n",
               defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("Defensor venceu!\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("Atacante perdeu 1 tropa. Agora tem %d tropas.\n", atacante->tropas);
        } else {
            printf("Atacante ja nao tem tropas para perder.\n");
        }
    }
}

// atribuirMissao: sorteia e copia a string para destino (destino deve ter malloc)
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// exibirMissao (por valor) mostra a missão para o jogador (apenas uma vez)
void exibirMissao(char *missao, char *nomeJogador) {
    printf("\n%s, sua missao: %s\n", nomeJogador, missao);
}

// verificarMissao: lógica simples, retorna 1 se cumprida, 0 caso contrario
// parametros: missao do jogador, mapa, tamanho do mapa, cor do jogador
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho, char *corJogador) {
    int i, conta = 0;
    // Missao 1: "Possuir 2 ou mais territorios"
    if (strstr(missao, "Possuir 2") != NULL) {
        for (i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) conta++;
        if (conta >= 2) return 1;
        return 0;
    }

    // Missao 2: "Ter um territorio com 5+ tropas"
    if (strstr(missao, "5+ tropas") != NULL) {
        for (i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 5) return 1;
        return 0;
    }

    // Missao 3: "Ser dono da maioria dos territorios"
    if (strstr(missao, "maioria") != NULL) {
        for (i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) conta++;
        if (conta > tamanho / 2) return 1;
        return 0;
    }

    // Missao 4: "Conquistar ao menos 1 territorio"
    if (strstr(missao, "ao menos 1") != NULL) {
        for (i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) return 1;
        return 0;
    }

    // Missao 5: "Eliminar todas tropas de um inimigo" (simples: verificar se existe algum outro cor com todas tropas 0)
    if (strstr(missao, "Eliminar todas tropas") != NULL) {
        // verificar se existe alguma cor diferente que nao tenha tropas (i.e., todas suas terras com tropas == 0)
        // simplificação: se existir ao meno uma cor que nao seja a do jogador e que nao tenha tropas no mapa
        // aqui vamos checar se há alguma cor A (diferente) tal que todas as suas territorios tenham 0 tropas
        int j, foundOther;
        // coleta lista de cores diferentes
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) continue;
            // verifica cor mapa[i].cor
            foundOther = 1; // assume que cor existe e pode estar zerada
            for (j = 0; j < tamanho; j++) {
                if (strcmp(mapa[j].cor, mapa[i].cor) == 0 && mapa[j].tropas > 0) {
                    foundOther = 0; // achou tropas nessa cor
                    break;
                }
            }
            if (foundOther) return 1;
        }
        return 0;
    }

    // default: não cumprida
    return 0;
}

// libera todas as memórias alocadas dinamicamente
void liberarMemoria(struct Territorio *mapa, char **missoesPlayer, int numPlayers) {
    int i;
    if (mapa != NULL) free(mapa);
    for (i = 0; i < numPlayers; i++) {
        if (missoesPlayer[i] != NULL) free(missoesPlayer[i]);
    }
    if (missoesPlayer != NULL) free(missoesPlayer);
}

int main() {
    srand(time(NULL));

    int qtdTerr, numPlayers;
    int i, op;
    struct Territorio *mapa = NULL;

    // vetor de missoes templates
    char *templates[] = {
        "Possuir 2 ou mais territorios",
        "Ter um territorio com 5+ tropas",
        "Ser dono da maioria dos territorios",
        "Conquistar ao menos 1 territorio",
        "Eliminar todas tropas de um inimigo"
    };
    int totalMissoes = 5;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtdTerr);
    getchar();

    // aloca mapa dinamicamente
    mapa = (struct Territorio*) malloc(qtdTerr * sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro: memoria\n");
        return 1;
    }

    // cadastra territorios (reaproveita funcao)
    cadastrar(mapa, qtdTerr);

    // jogadores
    printf("\nQuantos jogadores vao jogar? ");
    scanf("%d", &numPlayers);
    getchar();

    // arrays dinamicos para nomes, cores e missoes dos jogadores
    char **nomes = (char**) malloc(numPlayers * sizeof(char*));
    char **cores = (char**) malloc(numPlayers * sizeof(char*));
    char **missoesPlayer = (char**) malloc(numPlayers * sizeof(char*));

    for (i = 0; i < numPlayers; i++) {
        nomes[i] = (char*) malloc(MAX_NOME);
        cores[i] = (char*) malloc(MAX_COR);
        missoesPlayer[i] = (char*) malloc(100); // espaço pra copiar a missão

        printf("\nNome do jogador %d: ", i+1);
        fflush(stdin);
        fgets(nomes[i], MAX_NOME, stdin);
        nomes[i][strcspn(nomes[i], "\n")] = 0;

        printf("Cor do exercito do jogador (use mesma cor dos territorios ex: vermelho): ");
        fflush(stdin);
        fgets(cores[i], MAX_COR, stdin);
        cores[i][strcspn(cores[i], "\n")] = 0;

        // atribui missao dinamicamente (já alocado)
        atribuirMissao(missoesPlayer[i], templates, totalMissoes);

        // exibe missao apenas uma vez (pra jogador)
        exibirMissao(missoesPlayer[i], nomes[i]);
    }

    // jogo - loop principal
    do {
        printf("\n--- MENU MESTRE ---\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        if (op == 1) {
            exibirMapa(mapa, qtdTerr);
        }
        else if (op == 2) {
            exibirMapa(mapa, qtdTerr);
            int at, def, idxAt = -1, idxDef = -1;
            printf("\nEscolha numero do territorio atacante: ");
            scanf("%d", &at);
            getchar();
            printf("Escolha numero do territorio defensor: ");
            scanf("%d", &def);
            getchar();

            if (at < 1 || at > qtdTerr || def < 1 || def > qtdTerr) {
                printf("Erro: indice invalido\n");
                continue;
            }

            // valida se cores sao iguais
            if (strcmp(mapa[at-1].cor, mapa[def-1].cor) == 0) {
                printf("Erro: nao pode atacar territorio da mesma cor\n");
                continue;
            }
            // valida se atacante tem tropas > 0
            if (mapa[at-1].tropas <= 0) {
                printf("Erro: atacante nao tem tropas suficientes\n");
                continue;
            }

            // realiza ataque
            atacar(&mapa[at-1], &mapa[def-1]);

            // apos ataque, verificar missoes de todos jogadores (silencioso)
            for (i = 0; i < numPlayers; i++) {
                int ok = verificarMissao(missoesPlayer[i], mapa, qtdTerr, cores[i]);
                if (ok) {
                    printf("\n***** JOGADOR %s CUMPRIU A MISSAO! *****\n", nomes[i]);
                    printf("Missao: %s\n", missoesPlayer[i]);
                    // finalizar o jogo
                    liberarMemoria(mapa, missoesPlayer, numPlayers);
                    // liberar nomes e cores também
                    for (i = 0; i < numPlayers; i++) {
                        if (nomes[i]) free(nomes[i]);
                        if (cores[i]) free(cores[i]);
                    }
                    if (nomes) free(nomes);
                    if (cores) free(cores);
                    return 0;
                }
            }
        }

    } while (op != 0);

    // liberacoes finais caso saia sem vencedor
    liberarMemoria(mapa, missoesPlayer, numPlayers);

    for (i = 0; i < numPlayers; i++) {
        if (nomes[i]) free(nomes[i]);
        if (cores[i]) free(cores[i]);
    }
    if (nomes) free(nomes);
    if (cores) free(cores);

    printf("Finalizando jogo...\n");
    return 0;
}
