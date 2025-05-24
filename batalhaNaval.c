#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
#define AGUA '~'
#define BARCO 'B'
#define TIRO_ACERTO 'X'
#define TIRO_AGUA 'O'

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

void imprimirTabuleiro(char tabuleiro[TAM][TAM], int ocultar) {
    printf("  ");
    for (int i = 0; i < TAM; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (ocultar && tabuleiro[i][j] == BARCO)
                printf("%c ", AGUA);
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarBarcos(char tabuleiro[TAM][TAM], int qtdBarcos) {
    int x, y;
    for (int i = 0; i < qtdBarcos; i++) {
        do {
            printf("Digite a posição do barco #%d (linha coluna): ", i + 1);
            scanf("%d %d", &x, &y);
        } while (x < 0 || x >= TAM || y < 0 || y >= TAM || tabuleiro[x][y] == BARCO);
        tabuleiro[x][y] = BARCO;
    }
}

int atirar(char tabuleiro[TAM][TAM], int x, int y) {
    if (tabuleiro[x][y] == BARCO) {
        tabuleiro[x][y] = TIRO_ACERTO;
        return 1;
    } else if (tabuleiro[x][y] == AGUA) {
        tabuleiro[x][y] = TIRO_AGUA;
        return 0;
    }
    return -1; // Já atirado
}

int barcosRestantes(char tabuleiro[TAM][TAM]) {
    int contador = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == BARCO)
                contador++;
    return contador;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    char tabuleiro1[TAM][TAM], tabuleiro2[TAM][TAM];
    int x, y, jogadorAtual = 1, resultado, barcos = 3;

    inicializarTabuleiro(tabuleiro1);
    inicializarTabuleiro(tabuleiro2);

    printf("Jogador 1, posicione seus barcos:\n");
    posicionarBarcos(tabuleiro1, barcos);
    limparTela();

    printf("Jogador 2, posicione seus barcos:\n");
    posicionarBarcos(tabuleiro2, barcos);
    limparTela();

    while (1) {
        printf("Vez do Jogador %d\n", jogadorAtual);
        if (jogadorAtual == 1)
            imprimirTabuleiro(tabuleiro2, 1);
        else
            imprimirTabuleiro(tabuleiro1, 1);

        printf("Digite coordenadas do tiro (linha coluna): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            printf("Coordenadas inválidas. Tente novamente.\n");
            continue;
        }

        if (jogadorAtual == 1)
            resultado = atirar(tabuleiro2, x, y);
        else
            resultado = atirar(tabuleiro1, x, y);

        if (resultado == 1)
            printf("Acertou!\n");
        else if (resultado == 0)
            printf("Água!\n");
        else
            printf("Você já atirou aí!\n");

        if (barcosRestantes(jogadorAtual == 1 ? tabuleiro2 : tabuleiro1) == 0) {
            printf("Jogador %d venceu!\n", jogadorAtual);
            break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }

    return 0;
}
