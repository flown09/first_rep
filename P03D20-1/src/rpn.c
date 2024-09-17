#include "rpn.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "checks.h"
#include "stack.h"

double evaluate_rpn(const char* expression, double x_value) {
    Stack* stack = create_stack(100, sizeof(double));

    const char* token = expression;
    while (*token) {
        if (is_digit(*token)) {
            double value = atof(token);
            push(stack, &value);
            while (is_digit(*token) || *token == '.') token++;
        } else if (*token == 'x') {
            push(stack, &x_value);
            token++;
        } else if (is_operator(*token)) {
            double* b = (double*)pop(stack);
            double* a = (double*)pop(stack);
            double result;
            switch (*token) {
                case '+':
                    result = *a + *b;
                    break;
                case '-':
                    result = *a - *b;
                    break;
                case '*':
                    result = *a * *b;
                    break;
                case '/':
                    result = *a / *b;
                    break;
            }
            free(a);
            free(b);
            push(stack, &result);
            token++;
        } else if (*token == 's' || *token == 'c' || *token == 't' || *token == 'g' || *token == 'q' ||
                   *token == 'l') {
            double* value = (double*)pop(stack);
            double result = 0.0;
            if (*token == 's')
                result = sin(*value);
            else if (*token == 'c')
                result = cos(*value);
            else if (*token == 't')
                result = tan(*value);
            else if (*token == 'g')
                result = 1 / tan(*value);
            else if (*token == 'q')
                result = sqrt(*value);
            else if (*token == 'l')
                result = log(*value);
            free(value);
            push(stack, &result);
            token += (*token == 'q') ? 4 : 3;
        } else {
            token++;
        }
    }

    double* result = (double*)pop(stack);
    double final_result = *result;
    free(result);
    destroy_stack(stack);
    return final_result;
}