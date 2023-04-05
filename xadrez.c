#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define TAMANHO_TABULEIRO 8

typedef enum {
    VAZIO,
    PEAO,
    CAVALO,
    BISPO,
    TORRE,
    DAMA,
    REI
} tipoPecas;

typedef enum {
    BRANCO,
    PRETO
} corPeca;

typedef struct {
    tipoPecas tipo;
    corPeca cor;
} peca;

typedef struct {
    peca peca;
    bool seMoveu;
} pecaXadrez;

typedef struct {
    pecaXadrez peca;
    corPeca cor;
} jogador;

typedef struct {
    int coluna;
    int linha;
} casa; 

typedef struct {
    pecaXadrez peca;
    casa posicao;
} casaTabuleiro;

typedef struct {
    casaTabuleiro casas[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
} tabuleiroXadrez;

void iniciarTabuleiro(tabuleiroXadrez *tabuleiro) {
    for (int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for(int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro->casas[linha][coluna].peca.peca.tipo = VAZIO;
            tabuleiro->casas[linha][coluna].peca.seMoveu = false;
            tabuleiro->casas[linha][coluna].posicao.linha = linha;
            tabuleiro->casas[linha][coluna].posicao.coluna = coluna;
        }
    } 

    for(int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
        tabuleiro->casas[1][coluna].peca.peca.tipo = PEAO;
        tabuleiro->casas[1][coluna].peca.peca.cor = BRANCO;
        tabuleiro->casas[1][coluna].peca.seMoveu = false;
        tabuleiro->casas[6][coluna].peca.peca.tipo = PEAO;
        tabuleiro->casas[6][coluna].peca.peca.cor = PRETO;
        tabuleiro->casas[6][coluna].peca.seMoveu = false;
    }

    tabuleiro->casas[0][1].peca.peca.tipo = CAVALO;
    tabuleiro->casas[0][1].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][1].peca.seMoveu = false;
    tabuleiro->casas[0][6].peca.peca.tipo = CAVALO;
    tabuleiro->casas[0][6].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][6].peca.seMoveu = false;
    tabuleiro->casas[7][1].peca.peca.tipo = CAVALO;
    tabuleiro->casas[7][1].peca.peca.cor = PRETO;
    tabuleiro->casas[7][1].peca.seMoveu = false;
    tabuleiro->casas[7][6].peca.peca.tipo = CAVALO;
    tabuleiro->casas[7][6].peca.peca.cor = PRETO;
    tabuleiro->casas[7][6].peca.seMoveu = false;

    tabuleiro->casas[0][2].peca.peca.tipo = BISPO;
    tabuleiro->casas[0][2].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][2].peca.seMoveu = false;
    tabuleiro->casas[0][5].peca.peca.tipo = BISPO;
    tabuleiro->casas[0][5].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][5].peca.seMoveu = false;
    tabuleiro->casas[7][2].peca.peca.tipo = BISPO;
    tabuleiro->casas[7][2].peca.peca.cor = PRETO;
    tabuleiro->casas[7][2].peca.seMoveu = false;
    tabuleiro->casas[7][5].peca.peca.tipo = BISPO;
    tabuleiro->casas[7][5].peca.peca.cor = PRETO;
    tabuleiro->casas[7][5].peca.seMoveu = false;

    tabuleiro->casas[0][0].peca.peca.tipo = TORRE;
    tabuleiro->casas[0][0].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][0].peca.seMoveu = false;
    tabuleiro->casas[0][7].peca.peca.tipo = TORRE;
    tabuleiro->casas[0][7].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][7].peca.seMoveu = false;
    tabuleiro->casas[7][0].peca.peca.tipo = TORRE;
    tabuleiro->casas[7][0].peca.peca.cor = PRETO;
    tabuleiro->casas[7][0].peca.seMoveu = false;
    tabuleiro->casas[7][7].peca.peca.tipo = TORRE;
    tabuleiro->casas[7][7].peca.peca.cor = PRETO;
    tabuleiro->casas[7][7].peca.seMoveu = false;

    tabuleiro->casas[0][3].peca.peca.tipo = DAMA;
    tabuleiro->casas[0][3].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][3].peca.seMoveu = false;
    tabuleiro->casas[7][3].peca.peca.tipo = DAMA;
    tabuleiro->casas[7][3].peca.peca.cor = PRETO;
    tabuleiro->casas[7][3].peca.seMoveu = false;

    tabuleiro->casas[0][4].peca.peca.tipo = REI;
    tabuleiro->casas[0][4].peca.peca.cor = BRANCO;
    tabuleiro->casas[0][4].peca.seMoveu = false;
    tabuleiro->casas[7][4].peca.peca.tipo = REI;
    tabuleiro->casas[7][4].peca.peca.cor = PRETO;
    tabuleiro->casas[7][4].peca.seMoveu = false;
}

void gerarTabuleiro(tabuleiroXadrez tabuleiro) {
    printf("A B C D E F G H\n");
    
    for(int linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        printf("%d ", linha + 1);
        for(int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            int ehBranco = (linha + coluna) % 2 == 0;
            if (ehBranco) {
                printf("\033[47m"); 
            } else {
                printf("\033[40m"); 
            }
            tipoPecas tipo = tabuleiro.casas[linha][coluna].peca.peca.tipo;
            corPeca cor = tabuleiro.casas[linha][coluna].peca.peca.cor;
            char simbolo;
            switch(tipo) {
                case VAZIO:
                    simbolo = ' ';
                    break;

                case PEAO:
                    simbolo = 'P';
                    break;

                case CAVALO:
                    simbolo = 'C';
                    break;

                case BISPO:
                    simbolo = 'B';
                    break;

                case TORRE:
                    simbolo = 'T';
                    break;

                case DAMA:
                    simbolo = 'D';
                    break;

                case REI:
                    simbolo = 'R';
                    break;

            }
            printf("%c ", simbolo);
            printf("\033[00m");
        }
        printf("%d\n", linha + 1);
    }
    printf("a b c d e f g h\n");
}

bool moverPeca(tabuleiroXadrez *tabuleiro, tipoPecas tipo, casa origem, casa destino) {
    if(tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor == tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor) {
        return false;
    }

    switch(tipo) {
        case PEAO:
            if(tabuleiro->casas[origem.linha][origem.coluna].peca.seMoveu) {
                if (origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO) {
                    return true;
                }
                else if (origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo != VAZIO) {
                    return true;
                }
                else {
                    return false;
                }
            }else {
                if (origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO) {
                    return true;
                } else if (origem.coluna == destino.coluna && destino.linha == origem.linha + 2 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha + 1][origem.coluna].peca.peca.tipo == VAZIO) {
                    return true;
                } else if (origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo != VAZIO) {
                    return true;
                } else {
                    return false;
                }

            }
            break;
        case CAVALO:
            if ((destino.linha == origem.linha + 2 && destino.coluna == origem.coluna + 1) ||
                (destino.linha == origem.linha + 1 && destino.coluna == origem.coluna + 2) ||
                (destino.linha == origem.linha - 1 && destino.coluna == origem.coluna + 2) ||
                (destino.linha == origem.linha - 2 && destino.coluna == origem.coluna + 1) ||
                (destino.linha == origem.linha - 2 && destino.coluna == origem.coluna - 1) ||
                (destino.linha == origem.linha - 1 && destino.coluna == origem.coluna - 2) ||
                (destino.linha == origem.linha + 1 && destino.coluna == origem.coluna - 2) ||
                (destino.linha == origem.linha + 2 && destino.coluna == origem.coluna - 1)) {
                if (tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor || tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO) {
                    return true;
                } else {
                    return false;
                }
                } else {
                    return false;
                }
            break;
        case BISPO:
            if(abs(destino.coluna - origem.coluna) == abs(destino.linha - origem.linha)) {
                int colunaAtual = origem.coluna;
                int linhaAtual = origem.linha;
                int colunaDestino = destino.coluna;
                int linhaDestino = destino.linha;
                int colunaIncremento = (colunaDestino - colunaAtual > 0) ? 1 : -1;
                int linhaIncremento = (linhaDestino - linhaAtual > 0) ? 1 : -1;

                colunaAtual += colunaIncremento;
                linhaAtual += linhaIncremento;
                while(colunaAtual != colunaDestino && linhaAtual != linhaDestino) {
                    if(tabuleiro->casas[linhaAtual][colunaAtual].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                    colunaAtual += colunaIncremento;
                    linhaAtual += linhaIncremento;
                }

                return true;
            }else {
                return false;
            }
            break;
        
        case TORRE:
            break; 
    }
}

int main(void) {
    tabuleiroXadrez tabuleiro;
    iniciarTabuleiro(&tabuleiro);
    gerarTabuleiro(tabuleiro);

    /*char movimento[6];

    while(true) {
        printf("entre com um movimento (exp: e2e4): ");
        fgets(movimento, sizeof(movimento), stdin);
        if(strlen(movimento) < 4) {
            printf("movimento invalido...\n");
            continue;
        }

        casa origem 
    }*/
}