#include <stdio.h>
#include <string.h>
#include <ctype.h>
char* strlwr(char* str) {
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

int validarPlaca(const char *placa) {
    int comprimento = strlen(placa);

    if ((comprimento == 8 && placa[3] == '-' && isalpha(placa[0]) && isalpha(placa[1]) && isalpha(placa[2])) ||
        (comprimento == 7 && isalpha(placa[0]) && isalpha(placa[1]) && isalpha(placa[2]) &&
        isdigit(placa[3]) && isalpha(placa[4]) && isdigit(placa[5]) && isdigit(placa[6]))) {
        return 1;
    }

    return 0;
}

int validarDia(const char *dia) {
    const char *diasValidos[] = {"SEGUNDA-FEIRA", "TERCA-FEIRA", "QUARTA-FEIRA", "QUINTA-FEIRA", "SEXTA-FEIRA", "SABADO", "DOMINGO"};
    int numDias = sizeof(diasValidos) / sizeof(diasValidos[0]);

    for (int i = 0; i < numDias; i++) {
        if (strcmp(dia, diasValidos[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// Função imprimirResultado atualizada
int imprimirResultado(const char *placa, const char *dia, int placaValida, int diaValido, int podeCircular) {
    if (!placaValida) {
        printf("Placa invalida\n");
    }

    if (!diaValido) {
        printf("Dia da semana invalido\n");
    }

    if (podeCircular && (strcmp(dia, "SABADO") == 0 || strcmp(dia, "DOMINGO") == 0)) {
        printf("Nao ha proibicao no fim de semana\n");
    } else if (podeCircular) {
        printf("%s pode circular %s\n", placa, dia);
    } else if (placaValida && diaValido) {
        printf("%s nao pode circular %s\n", placa, dia);
    }

    return 0;
}


int verificarRodizio(const char *placa, const char *dia) {
    int terminacao = placa[strlen(placa) - 1] - '0';
    char diaUpper[15];
    strcpy(diaUpper, dia);

    for (int i = 0; diaUpper[i]; i++) {
        diaUpper[i] = tolower(dia[i]);
    }

    // Usando switch case para verificar o rodízio
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

    // Convertendo para maiúsculas
    for (int i = 0; placa[i]; i++) {
        placa[i] = toupper(placa[i]);
    }
    for (int i = 0; dia[i]; i++) {
        dia[i] = toupper(dia[i]);
    }

    int placaValida = validarPlaca(placa);
    int diaValido = validarDia(dia);

    if (!placaValida || !diaValido) {
        imprimirResultado(placa, dia, placaValida, diaValido, 0);
        return 0;
    }

    int podeCircular = !verificarRodizio(placa, dia);
    // Alterando a saída para que o dia da semana esteja em minúsculo
    imprimirResultado(placa, strlwr(dia), placaValida, diaValido, podeCircular);

    return 0;
}
