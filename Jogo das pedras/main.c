#include <stdio.h>

// Inicializar o tabuleiro
void inic_tab(char m[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i <= 1 || i >= 6 || j <= 1 || j >= 6) {
                m[i][j] = '*';
            } else {
                m[i][j] = '-';
            }
        }
    }
}

// Apresentar o tabuleiro
void apr_tab(char m[8][8]) {
    printf("  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

// Verificar se a casa est� vazia
int casa_vazia(char m[8][8], int lin, int col) {
    return m[lin][col] == '-';
}

// Verificar se o salto � v�lido
int salto_valido(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    if (lin_d < 0 || lin_d >= 8 || col_d < 0 || col_d >= 8) {                   //salto n�o � valido para valores fora do tabuleiro
        return 0;
    }

    int lin_diff = lin_d - lin_o;
    int col_diff = col_d - col_o;

    if (lin_diff % 2 == 0 && col_diff % 2 == 0) {
        int lin_inter = lin_o + lin_diff / 2;
        int col_inter = col_o + col_diff / 2;

        if (m[lin_inter][col_inter] == '*') {
            return 1;
        }
    }

    return 0;
}

// Contar o n�mero de pedras no tabuleiro
int contar_pedras(char m[8][8]) {
    int contador = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (m[i][j] == '*') {
                contador++;
            }
        }
    }
    return contador;
}

// Eliminar pedras no tabuleiro entre as coordenadas
void eliminar_pedras(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    int lin_diff = (lin_d - lin_o) / 2;
    int col_diff = (col_d - col_o) / 2;
    int lin_inter = lin_o + lin_diff;
    int col_inter = col_o + col_diff;

    while (lin_inter != lin_d || col_inter != col_d) {
        m[lin_inter][col_inter] = '-';                                          // Deixa a casa intermedi�ria vazia
        lin_inter = lin_inter + lin_diff;
        col_inter = col_inter + col_diff;
    }

    m[lin_d][col_d] = '*';                                                      // Move a pedra para a casa de destino
    m[lin_o][col_o] = '-';                                                      // Deixa a casa de origem vazia
}

// Verificar a possibilidade de salto com pedras intermedi�rias
int verificar_possibilidade_de_salto(char m[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (m[i][j] == '*') {
                // Verificar se h� pelo menos uma casa dispon�vel para um salto com pedra
                if ((i >= 2 && casa_vazia(m, i - 2, j)) ||
                    (i <= 5 && casa_vazia(m, i + 2, j)) ||
                    (j >= 2 && casa_vazia(m, i, j - 2)) ||
                    (j <= 5 && casa_vazia(m, i, j + 2))) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    char tab[8][8];  // Tabuleiro (representa��o)
    int lin_o, col_o, lin_d, col_d;  // Dados da jogada
    int saltos = 0;
    int pedras_elim = 0;

    // Inicializar o tabuleiro
    inic_tab(tab);

    do {
        // Apresentar o tabuleiro
        apr_tab(tab);

        // Solicitar a casa de origem
        printf("\nDigite a linha da casa de origem (1-8) ou 0 para desistir: ");
        scanf("%d", &lin_o);
        if (lin_o == 0) {
            break;
        }
        printf("\nDigite a coluna da casa de origem (1-8) ou 0 para desistir: ");
        scanf("%d", &col_o);
        if (col_o == 0) {
            break;
        }

        // Verificar se a casa de origem cont�m uma pedra
        if (!casa_vazia(tab, lin_o - 1, col_o - 1)) {
            // Solicitar a casa de destino
            printf("\nDigite a linha da casa de destino (1-8) ou 0 para desistir: ");
            scanf("%d", &lin_d);
            if (lin_d == 0) {
                break;
            }
            printf("\nDigite a coluna da casa de destino (1-8) ou 0 para desistir: ");
            scanf("%d", &col_d);
            if (col_d == 0) {
                break;
            }

            // Verificar se o salto � v�lido
            if (salto_valido(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1)) {
                // Verificar se a casa de destino est� vazia
                if (casa_vazia(tab, lin_d - 1, col_d - 1)) {
                    // Executar o salto e eliminar as pedras
                    eliminar_pedras(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1);
                    saltos++;
                    int pedras_salto = (((lin_d - lin_o - 1) + (col_d - col_o - 1)) / 2);
                    if(pedras_salto < 0) {
                        pedras_salto = - pedras_salto;
                    }
                    pedras_elim = pedras_elim + pedras_salto;
                    printf("\nSalto de (%d,%d) para (%d,%d) com %d pedra(s) eliminada(s) neste salto.\n", lin_o, col_o, lin_d, col_d, pedras_salto);
                    printf("%d pedras eliminadas; restam %d pedras no tabuleiro.\n", pedras_elim, contar_pedras(tab));
                } else {
                    printf("\nA casa de destino n�o est� vazia. Tente novamente.\n");
                }
            } else {
                printf("\nSalto inv�lido. Tente novamente.\n");
            }
        } else {
            printf("\nA casa de origem n�o cont�m uma pedra. Tente novamente.\n");
        }
    } while (verificar_possibilidade_de_salto(tab));

    // Mostrar estat�sticas
    printf("Jogo encerrado.\n");
    printf("N�mero de saltos realizados: %d\n", saltos);
    printf("Quantidade de pedras eliminadas: %d\n", pedras_elim);

    // Determinar o n�vel de dificuldade atingido
    int pedras_restantes = contar_pedras(tab);
    printf("N�vel de dificuldade atingido: ");
    if (pedras_restantes >= 45) {
        printf("Extremamente dif�cil\n");
    } else if (pedras_restantes >= 40) {
        printf("Dif�cil\n");
    } else if (pedras_restantes >= 30) {
        printf("F�cil\n");
    } else {
        printf("Extremamente f�cil\n");
    }

    // Perguntar ao jogador se deseja jogar novamente
    char jogar_novamente;
    printf("Deseja jogar novamente? (S/N): ");
    scanf(" %c", &jogar_novamente);

    if (jogar_novamente == 'S' || jogar_novamente == 's') {
        // Reiniciar o jogo
        printf("\n");
        main();
    } else {
        printf("Fim do jogo.\n");
    }

    return 0;
}



