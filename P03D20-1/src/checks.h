#ifndef CHECKS_H
#define CHECKS_H

int is_digit(char ch);
int is_operator(char ch);
int precedence(char op);
int is_function(const char* token);

#endif