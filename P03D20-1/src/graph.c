#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infix_to_rpn.h"
#include "rpn.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 25
#define X_MAX (4 * M_PI)
#define Y_MAX 1.0
#define Y_MIN -1.0

int normalize_y(double y) { return (int)round((HEIGHT - 1) * (1.0 - (y - Y_MIN) / (Y_MAX - Y_MIN))); }

void plot_graph(const char* rpn_expression) {
    char screen[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = '.';
        }
    }
    int num_points = WIDTH * 4;
    for (int x_pixel = 0; x_pixel < num_points; x_pixel++) {
        double x = X_MAX * x_pixel / (num_points - 1);
        double y = evaluate_rpn(rpn_expression, x);
        int y_pixel = normalize_y(y);
        if (y_pixel >= 0 && y_pixel < HEIGHT) {
            int screen_x = x_pixel * WIDTH / num_points;
            screen[y_pixel][screen_x] = '*';
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(screen[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    char infix_expression[256];
    fgets(infix_expression, 256, stdin);
    char* rpn_expression = infix_to_rpn(infix_expression);
    plot_graph(rpn_expression);
    free(rpn_expression);
    return 0;
}
