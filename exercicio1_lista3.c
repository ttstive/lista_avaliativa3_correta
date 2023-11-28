#include <stdio.h>
#include <string.h>

int valores_romano(char roman) {
    switch (roman) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return -1;
    }
}

void transform_binary(int b) {
    if (b > 1) {
        transform_binary(b / 2);
    }
    printf("%d", b % 2);
}

void transform_hex(int num) {
    if (num == 0) {
        printf("Hexadecimal: 0\n");
        return;
    }

    char hex_num[12]; 
    int i = 0;

    while (num != 0) {
        int temp = num % 16;

        if (temp < 10) {
            hex_num[i] = temp + '0';
        } else {
            hex_num[i] = temp - 10 + 'a'; 
        }

        num = num / 16;
        i++;
    }

    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hex_num[j]);
    }
    printf("\n");
}

int transform_decimal(char *num) {
    int srt = 0;
    int length = strlen(num);

    for (int i = 0; i < length; i++) {
        int current = valores_romano(num[i]);

        if (i + 1 < length) {
            int next = valores_romano(num[i + 1]);

            if (current >= next) {
                srt += current;
            } else {
                srt += next - current;
                i++;
            }
        } else {
            srt += current;
            i++;
        }
    }
    return srt;
}

int main() {
    char roman_numeral[13]; 
    fgets(roman_numeral, 13, stdin); 

    // Remove newline character if present
    size_t len = strlen(roman_numeral);
    if (len > 0 && roman_numeral[len-1] == '\n') {
        roman_numeral[--len] = '\0';
    }

    int decimal_value = transform_decimal(roman_numeral);
    if (decimal_value != -1) {
        printf("%s na base 2: ", roman_numeral);
        transform_binary(decimal_value);
        printf("\n"); 
        printf("%s na base 10: %d\n", roman_numeral, decimal_value);

        printf("%s na base 16: ", roman_numeral);
        transform_hex(decimal_value);
    } else {
        printf("Invalid Roman numeral: %s\n", roman_numeral);
    }

    return 0;
}
