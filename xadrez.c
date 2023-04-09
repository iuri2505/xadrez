#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define TAMANHO_TABULEIRO 8

bool reiVivo = true;
int numTurno = 1;

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
    int linha;
    int coluna;
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
    printf("  A B C D E F G H\n");
    
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
            if(cor == BRANCO) {
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
            }else {
                switch(tipo) {
                    case VAZIO:
                        simbolo = ' ';
                        break;

                    case PEAO:
                        simbolo = 'p';
                        break;

                    case CAVALO:
                        simbolo = 'c';
                        break;

                    case BISPO:
                        simbolo = 'b';
                        break;

                    case TORRE:
                        simbolo = 't';
                        break;

                    case DAMA:
                        simbolo = 'd';
                        break;

                    case REI:
                        simbolo = 'r';
                        break;
                }
            }
            printf("%c ", simbolo);
            printf("\033[00m");
        }
        printf(" %d\n", linha + 1);
    }
    printf("  a b c d e f g h\n");
}

void checarRei(tabuleiroXadrez *tabuleiro, casa destino) {
    if(tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == REI) {
        reiVivo = false;
    }
}

int checarTurno(int numTurno) {
    int turno;
    if(numTurno % 2 != 0) {
        turno = BRANCO;
    }else {
        turno = PRETO;
    }

    return turno;
}

bool moverPeca(tabuleiroXadrez *tabuleiro, tipoPecas tipo, casa origem, casa destino) {
    int turno = checarTurno(numTurno);

    if(turno == BRANCO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != BRANCO) {
        return false;
    }else if(turno == PRETO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != PRETO) {
        return false;
    }

    switch(tipo) {
        case VAZIO:
            return false;    
            break;
        
        case PEAO:
            if(tabuleiro->casas[origem.linha][origem.coluna].peca.seMoveu) {
                if((origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == BRANCO) ||
                    (origem.coluna == destino.coluna && destino.linha == origem.linha - 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == PRETO)) {
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                    tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.seMoveu = true;
                    return true;
                }
                else if(abs(destino.linha - origem.linha) == 1 && abs(destino.coluna - origem.coluna) == 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo != VAZIO) {
                    checarRei(tabuleiro, destino);
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                    tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.seMoveu = true;
                    return true;
                    
                }
                else {
                    return false;
                    
                }
            }else {
                if((origem.coluna == destino.coluna && destino.linha == origem.linha + 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == BRANCO) || 
                    (origem.coluna == destino.coluna && destino.linha == origem.linha - 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == PRETO)){
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                    tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.seMoveu = true;
                    return true;
                    
                } else if((origem.coluna == destino.coluna && destino.linha == origem.linha + 2 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha + 1][origem.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == BRANCO) ||
                    (origem.coluna == destino.coluna && destino.linha == origem.linha - 2 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha - 1][origem.coluna].peca.peca.tipo == VAZIO && tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor == PRETO)) {
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                    tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.seMoveu = true;
                    return true;
                    
                } else if(abs(destino.linha - origem.linha) == 1 && abs(destino.coluna - origem.coluna) == 1 && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor && tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo != VAZIO) {
                    checarRei(tabuleiro, destino);
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                    tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                    tabuleiro->casas[destino.linha][destino.coluna].peca.seMoveu = true;
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
                    if (tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor || 
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    } else {
                        return false;
                    }
                }else {
                    return false;
                }
            break;
        case BISPO:
            if(abs(destino.coluna - origem.coluna) == abs(destino.linha - origem.linha)) {
                int colunaAtual = origem.coluna;
                int linhaAtual = origem.linha;
                int colunaIncremento = (destino.coluna - colunaAtual > 0) ? 1 : -1;
                int linhaIncremento = (destino.linha - linhaAtual > 0) ? 1 : -1;

                do {
                    colunaAtual += colunaIncremento;
                    linhaAtual += linhaIncremento;
                    if(colunaAtual == destino.coluna && linhaAtual == destino.linha && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[linhaAtual][colunaAtual].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[linhaAtual][colunaAtual].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(colunaAtual != destino.coluna && linhaAtual != destino.linha);
            }else {
                return false;
            }
            break;
        
        case TORRE:
            if(abs(origem.coluna - destino.coluna) > 0 && origem.linha == destino.linha) {
                int colunaAtual = origem.coluna;
                int colunaIncremento = (destino.coluna - origem.coluna > 0) ? 1 : -1;
                do {
                    colunaAtual += colunaIncremento;
                    if(colunaAtual == destino.coluna && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[destino.linha][colunaAtual].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(colunaAtual < destino.coluna);

            }else if(abs(origem.linha - destino.linha) > 0 && origem.coluna == destino.coluna) {
                int linhaAtual = origem.linha;
                int linhaIncremento = (destino.linha - origem.linha > 0) ? 1 : -1;
                do {
                    linhaAtual += linhaIncremento;
                    if(linhaAtual == destino.linha && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[linhaAtual][destino.coluna].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(linhaAtual < destino.linha);

            }else {
                return false;
            }
            break; 

        case DAMA: 
            if(abs(destino.coluna - origem.coluna) == abs(destino.linha - origem.linha)) {
                int colunaAtual = origem.coluna;
                int linhaAtual = origem.linha;
                int colunaIncremento = (destino.coluna - colunaAtual > 0) ? 1 : -1;
                int linhaIncremento = (destino.linha - linhaAtual > 0) ? 1 : -1;

                do {
                    colunaAtual += colunaIncremento;
                    linhaAtual += linhaIncremento;
                    if(colunaAtual == destino.coluna && linhaAtual == destino.linha && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[linhaAtual][colunaAtual].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[linhaAtual][colunaAtual].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(colunaAtual != destino.coluna && linhaAtual != destino.linha);
            }else if(abs(origem.coluna - destino.coluna) > 0 && origem.linha == destino.linha) {
                int colunaAtual = origem.coluna;
                int colunaIncremento = (destino.coluna - origem.coluna > 0) ? 1 : -1;
                do {
                    colunaAtual += colunaIncremento;
                    if(colunaAtual == destino.coluna && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[destino.linha][colunaAtual].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(colunaAtual < destino.coluna);


            }else if(abs(origem.linha - destino.linha) > 0 && origem.coluna == destino.coluna) {
                int linhaAtual = origem.linha;
                int linhaIncremento = (destino.linha - origem.linha > 0) ? 1 : -1;
                do {
                    linhaAtual += linhaIncremento;
                    if(linhaAtual == destino.linha && (tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor != tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor || tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO)) {
                        checarRei(tabuleiro, destino);
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                        tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                        tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                        return true;
                    }else if(tabuleiro->casas[linhaAtual][destino.coluna].peca.peca.tipo != VAZIO) {
                        return false;
                    }
                }while(linhaAtual < destino.linha);

            }else {
                return false;
            } 
            break;

        case REI:
            if(((abs(destino.coluna - origem.coluna) == 1 && abs(destino.linha - origem.linha) == 0) || 
                (abs(destino.linha - origem.linha) == 1 && abs(destino.coluna - origem.coluna) == 0) || 
                (abs(destino.linha - origem.linha) == 1 && abs(destino.coluna - origem.coluna) == 1)) &&
                ((tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor != tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor) ||
                tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo == VAZIO)) {
                checarRei(tabuleiro, destino);
                tabuleiro->casas[destino.linha][destino.coluna].peca.peca.tipo = tipo;
                tabuleiro->casas[origem.linha][origem.coluna].peca.peca.tipo = VAZIO;
                tabuleiro->casas[destino.linha][destino.coluna].peca.peca.cor = tabuleiro->casas[origem.linha][origem.coluna].peca.peca.cor;
                return true;
            }else {
                return false;
            }
            break;
        
        default:
        return false;    
        break;
    
    }
    return false;
}

bool gerarMovimento(tabuleiroXadrez *tabuleiro, char movimento[6]) {
    char linhaOrigem[2] = {movimento[0],'\0'};
    char colunaOrigem = movimento[1];
    char linhaDestino[2] = {movimento[2],'\0'};
    char colunaDestino = movimento[3];
    int numColunaOrigem;
    int numColunaDestino;
    
    switch(colunaOrigem){
        case 'a':
            numColunaOrigem = 0;
            break;
        case 'b':
            numColunaOrigem = 1;
            break;
        case 'c':
            numColunaOrigem = 2;
            break;
        case 'd':
            numColunaOrigem = 3;
            break;
        case 'e':
            numColunaOrigem = 4;
            break;
        case 'f':
            numColunaOrigem = 5;
            break;
        case 'g':
            numColunaOrigem = 6;
            break;
        case 'h':
            numColunaOrigem = 7;
            break;
    }
    int numLinhaOrigem = atoi(linhaOrigem);
    int numLinhaDestino = atoi(linhaDestino);
    switch(colunaDestino){
        case 'a':
            numColunaDestino = 0;
            break;
        case 'b':
            numColunaDestino = 1;
            break;
        case 'c':
            numColunaDestino = 2;
            break;
        case 'd':
            numColunaDestino = 3;
            break;
        case 'e':
            numColunaDestino = 4;
            break;
        case 'f':
            numColunaDestino = 5;
            break;
        case 'g':
            numColunaDestino = 6;
            break;
        case 'h':
            numColunaDestino = 7;
            break;
    }
    
    numLinhaDestino--;
    numLinhaOrigem--;
    casa origem = {numLinhaOrigem, numColunaOrigem};
    casa destino = {numLinhaDestino, numColunaDestino};
    tipoPecas tipo = tabuleiro->casas[numLinhaOrigem][numColunaOrigem].peca.peca.tipo;
    bool valido = moverPeca(tabuleiro, tipo, origem, destino);
    return valido;
}

int main(void) {
    tabuleiroXadrez tabuleiro;
    iniciarTabuleiro(&tabuleiro);
    gerarTabuleiro(tabuleiro);

    char movimento[6];
    bool movimentoValido = false;

    while(reiVivo) {
        while(!movimentoValido) {
            int turno = checarTurno(numTurno);
            if(turno == BRANCO) {
                printf("entre com o movimento jogador 1: ");
            }else {
                printf("entre com o movimento jogador 2: ");
            }
            gets(movimento);
            if(strlen(movimento) == 4) {
                movimentoValido = true;
            }else {
                printf("comando invalido...\n");
            }
        }
        movimentoValido = false;
    
        bool valido = gerarMovimento(&tabuleiro, movimento);

        if(valido) {
            gerarTabuleiro(tabuleiro);
            numTurno++;
        }else {
            printf("comando invalido...\n");
        }
    }
}