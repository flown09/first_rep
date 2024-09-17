#include "infix_to_rpn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checks.h"
#include "stack.h"

char* infix_to_rpn(const char* expression) {
    Stack* stack = create_stack(100, sizeof(char));
    char* output = (char*)malloc(256 * sizeof(char));
    int output_pos = 0;

    const char* token = expression;
    while (*token) {
        if (is_digit(*token) || *token == 'x') {
            while (is_digit(*token) || *token == 'x' || *token == '.') {
                output[output_pos++] = *token++;
            }
            output[output_pos++] = ' ';
        } else if (is_function(token)) {
            if (strncmp(token, "sin", 3) == 0) {
                push(stack, "s");
                token += 3;
            } else if (strncmp(token, "cos", 3) == 0) {
                push(stack, "c");
                token += 3;
            } else if (strncmp(token, "tan", 3) == 0) {
                push(stack, "t");
                token += 3;
            } else if (strncmp(token, "ctg", 3) == 0) {
                push(stack, "g");
                token += 3;
            } else if (strncmp(token, "sqrt", 4) == 0) {
                push(stack, "q");
                token += 4;
            } else if (strncmp(token, "ln", 2) == 0) {
                push(stack, "l");
                token += 2;
            }
        } else if (*token == '(') {
            push(stack, token);
            token++;
        } else if (*token == ')') {
            while (*(char*)peek(stack) != '(') {
                char* value = (char*)pop(stack);
                output[output_pos++] = *value;
                output[output_pos++] = ' ';
                free(value);
            }
            const char* func = (char*)peek(stack);
            if (func != NULL && (*func == 's' || *func == 'c' || *func == 't' || *func == 'g' ||
                                 *func == 'q' || *func == 'l')) {
                char* value = (char*)pop(stack);
                output[output_pos++] = *value;
                output[output_pos++] = ' ';
                free(value);
            }
            token++;
        } else if (is_operator(*token)) {
            while (stack->top != -1 && precedence(*(char*)peek(stack)) >= precedence(*token)) {
                char* value = (char*)pop(stack);
                output[output_pos++] = *value;
                output[output_pos++] = ' ';
                free(value);
            }
            push(stack, token);
            token++;
        } else {
            token++;
        }
    }

    while (stack->top != -1) {
        char* value = (char*)pop(stack);
        output[output_pos++] = *value;
        output[output_pos++] = ' ';
        free(value);
    }

    output[output_pos] = '\0';
    destroy_stack(stack);
    return output;
}