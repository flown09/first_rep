#include <string.h>

int is_digit(char ch) { return ch >= '0' && ch <= '9'; }

int is_operator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int is_function(const char* token) {
    return (strncmp(token, "sin", 3) == 0 || strncmp(token, "cos", 3) == 0 || strncmp(token, "tan", 3) == 0 ||
            strncmp(token, "ctg", 3) == 0 || strncmp(token, "sqrt", 4) == 0 || strncmp(token, "ln", 2) == 0);
}