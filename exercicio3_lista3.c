#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validarPlaca(char *placa) {
    int formatoValido = 0;
    int comprimento = strlen(placa);

    if (comprimento == 8 && placa[3] == '-' && isalpha(placa[0]) && isalpha(placa[1]) && isalpha(placa[2])) {
        formatoValido = 1;
    } else if (comprimento == 7 && isalpha(placa[0]) && isalpha(placa[1]) && isalpha(placa[2]) &&
               isdigit(placa[3]) && isalpha(placa[4]) && isdigit(placa[5]) && isdigit(placa[6])) {
        formatoValido = 1;
    }

    return formatoValido;
}

int validarDia(char *dia) {
    char diasValidos[7][15] = {"SEGUNDA-FEIRA", "TERCA-FEIRA", "QUARTA-FEIRA", "QUINTA-FEIRA", "SEXTA-FEIRA", "SABADO", "DOMINGO"};
    int diaValido = 0;

    for (int i = 0; i < 7; i++) {
        if (strcmp(dia, diasValidos[i]) == 0) {
            diaValido = 1;
            break;
        }
    }

    return diaValido;
}

int imprimirResultado(char *placa, char *dia, int placaValida, int diaValido, int podeCircular) {
    char diaLower[15];
    strcpy(diaLower, dia);
    strlwr(diaLower);

    if (!placaValida) {
        printf("Placa invalida\n");
    }

    if (!diaValido) {
        printf("Dia da semana invalido\n");
    }

    if (podeCircular && (strcmp(dia, "SABADO") == 0 || strcmp(dia, "DOMINGO") == 0)) {
        printf("Nao ha proibicao no fim de semana\n");
    } else if (podeCircular) {
        printf("%s pode circular %s\n", placa, diaLower);
    } else if (placaValida && diaValido) {
        printf("%s nao pode circular %s\n", placa, diaLower);
    }

    return 0;
}

int verificarRodizio(const char *placa, const char *dia) {
    int terminacao = placa[strlen(placa) - 1] - '0';

    switch (terminacao) {
        case 0:
        case 1:
            if (strcmp(dia, "SEGUNDA-FEIRA") == 0) {
                return 1;
            }
            break;
        case 2:
        case 3:
            if (strcmp(dia, "TERCA-FEIRA") == 0) {
                return 1;
            }
            break;
        case 4:
        case 5:
            if (strcmp(dia, "QUARTA-FEIRA") == 0) {
                return 1;
            }
            break;
        case 6:
        case 7:
            if (strcmp(dia, "QUINTA-FEIRA") == 0) {
                return 1;
            }
            break;
        case 8:
        case 9:
            if (strcmp(dia, "SEXTA-FEIRA") == 0) {
                return 1;
            }
            break;
        default:
            return 0;
    }

    return 0;
}

int main() {
    char placa[20];
    char dia[15];

    scanf("%s", placa);
    scanf("%s", dia);

    int placaValida = validarPlaca(placa);
    int diaValido = validarDia(dia);

    if (!placaValida || !diaValido) {
        imprimirResultado(placa, dia, placaValida, diaValido, 0);
        return 0;
    }

    int podeCircular = !verificarRodizio(placa, dia);
    imprimirResultado(placa, dia, placaValida, diaValido, podeCircular);

    return 0;
}
