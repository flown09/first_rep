#include <stdio.h>
#include <stdlib.h>

#define ROWS 80
#define COLS 25

void printBoard(char const game_pole[ROWS][COLS]);
void inputFromFile(char const *string, char game_pole[ROWS][COLS]);
void nextStep(char game_pole[ROWS][COLS]);
int count_live_neighbors(char const game_pole[ROWS][COLS], int n, int m);
void menu(int option, char game_pole[ROWS][COLS]);

int main(void) {
    char game_pole[ROWS][COLS];

    int sleep = 2000000000, counter = -sleep, speed, option;
    printf("Введите скорость: ");
    scanf("%d", &speed);

    do {
        printf("Какой файл вы хотите выбрать?(ввести цифру)\n");
        printf("1 - butterfly.txt\n");
        printf("2 - glider.txt\n");
        printf("3 - switch_engine.txt\n");
        printf("4 - Gosper_glider_gun.txt\n");
        printf("5 - edgeshot_blinker.txt\n");
        printf("6 - 21_school.txt\n");
        printf("Ваш выбор: ");
        scanf("%d", &option);
    } while (option < 1 || option > 6);
    menu(option, game_pole);

    while (1) {
        printf("\033c");
        printBoard(game_pole);
        nextStep(game_pole);
        while (counter * speed < sleep) counter++;
        counter = -sleep;
    }

    return 0;
}

void menu(int option, char game_pole[ROWS][COLS]) {
    switch (option) {
        case 1:
            inputFromFile("butterfly.txt", game_pole);
            break;
        case 2:
            inputFromFile("glider.txt", game_pole);
            break;
        case 3:
            inputFromFile("switch_engine.txt", game_pole);
            break;
        case 4:
            inputFromFile("Gosper_glider_gun.txt", game_pole);
            break;
        case 5:
            inputFromFile("edgeshot_blinker.txt", game_pole);
            break;
        case 6:
            inputFromFile("21_school.txt", game_pole);
            break;
    }
}

void printBoard(char const game_pole[ROWS][COLS]) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%c", game_pole[j][i]);
        }
        putchar('\n');
    }
}

int count_live_neighbors(char const game_pole[ROWS][COLS], int n, int m) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int dm = (m + j + COLS) % COLS;
            int dn = (n + i + ROWS) % ROWS;
            if (game_pole[dn][dm] == '0') count++;
        }
    }
    return count;
}

void nextStep(char game_pole[ROWS][COLS]) {
    char nextStep[ROWS][COLS] = {{' '}};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int cells_around = count_live_neighbors(game_pole, i, j);

            if (game_pole[i][j] == '0') {
                if (cells_around < 2 || cells_around > 3)
                    nextStep[i][j] = ' ';
                else
                    nextStep[i][j] = '0';
            } else {
                if (cells_around == 3)
                    nextStep[i][j] = '0';
                else
                    nextStep[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            game_pole[i][j] = nextStep[i][j];
        }
    }
}

void inputFromFile(char const *filename, char game_pole[ROWS][COLS]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            int ch = fgetc(f);

            if (ch == EOF) {
                game_pole[j][i] = ' ';
            } else {
                game_pole[j][i] = ch;
            }
        }

        if (fgetc(f) == EOF) {
            break;
        }
    }

    fclose(f);
}