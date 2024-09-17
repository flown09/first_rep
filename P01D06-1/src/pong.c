 #include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

// Начальные координаты шарика
int ball_x = WIDTH / 2;
int ball_y = HEIGHT / 2;

// Вектор направления движения шарика
int vector_x = -1;
int vector_y = 1;

// Функция отрисовки поля и ракеток
void draw_field(int pos_l, int pos_r, int score_r, int score_l) {
    for (int k = 0; k < 37; k++) {
        printf(" ");
    }
    if (score_l <= 9 && score_r != 21)
        printf("%d     %d\n", score_l, score_r);
    else if (score_l == 21)
        printf("\b\b\bWIN LEFT GAMER\n");
    else if (score_r == 21)
        printf("\b\b\bWIN RIGHT GAMER\n");
    else if (score_l >= 10 && score_l < 21)
        printf("%d   %d\n", score_l, score_r);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                printf("*");
            } else if (j == ball_x && i == ball_y) {
                printf("o");
            } else if (((j == 4) && (i == pos_l || i == pos_l - 1 || i == pos_l + 1)) ||
                       ((j == 75) && (i == pos_r || i == pos_r - 1 || i == pos_r + 1))) {
                printf("|");
            } else if (j == 40)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void ball(int pos_l, int pos_r) {
    if (ball_y == 1 || ball_y == HEIGHT - 2) {
        vector_y = -vector_y;
    }

    // Проверка столкновения с левой ракеткой
    if (ball_x == 5 && (ball_y == pos_l || ball_y == pos_l - 1 || ball_y == pos_l + 1)) {
        vector_x = -vector_x;
    }

    // Проверка столкновения с правой ракеткой
    if (ball_x == 74 && (ball_y == pos_r || ball_y == pos_r - 1 || ball_y == pos_r + 1)) {
        vector_x = -vector_x;
    }

    // Изменение положения шарика
    ball_x += vector_x;
    ball_y += vector_y;
}

// Функция для движения левой ракетки
int move_left_paddle(int left_paddle_pos, char button) {
    if ((button == 'a' || button == 'A') && left_paddle_pos != 2) {
        left_paddle_pos--;
    } else if ((button == 'z' || button == 'Z') && left_paddle_pos != 22) {
        left_paddle_pos++;
    }
    return left_paddle_pos;
}

// Функция для движения правой ракетки
int move_right_paddle(int right_paddle_pos, char button) {
    if ((button == 'k' || button == 'K') && right_paddle_pos != 2) {
        right_paddle_pos--;
    } else if ((button == 'm' || button == 'M') && right_paddle_pos != 22) {
        right_paddle_pos++;
    }
    return right_paddle_pos;
}
// Функция выхода из игры
int quit_game() {
    int quit_button;
    printf("Are you sure you wanna quit? y/n\n");
    do {
        quit_button = getchar();
        if (quit_button == 'y')
            return 3;
        else if (quit_button == 'n')
            return 1;
    } while (quit_button != 'y' && quit_button != 'n');
    return 0;
}

// Функция старта игры
int start_game(int left_paddle_pos, int right_paddle_pos) {
    int exit = 1;
    int score_r = 19;
    int score_l = 19;
    while (exit != 0 && exit != 2 && exit != 3) {
        char button;
        printf("\033c");
        draw_field(left_paddle_pos, right_paddle_pos, score_r, score_l);
        if (score_l == 21) {
            exit = 0;
        } else if (score_r == 21) {
            exit = 2;
        }
        ball(left_paddle_pos, right_paddle_pos);
        if (ball_x == 0) {
            score_r++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
        } else if (ball_x == 79) {
            score_l++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
        }
        button = getchar();
        if (button == 'q') {
            exit = quit_game();
        } else if (button == 'a' || button == 'z' || button == 'k' || button == 'm') {
            left_paddle_pos = move_left_paddle(left_paddle_pos, button);
            right_paddle_pos = move_right_paddle(right_paddle_pos, button);
        }
    }
    return 0;
}

int main(void) {
    int left_paddle_pos = 12;
    int right_paddle_pos = 12;

    start_game(left_paddle_pos, right_paddle_pos);
    return 0;
}
