#ifndef SRC_SUPERCALC_SIMPLE_STACK_H_
#define SRC_SUPERCALC_SIMPLE_STACK_H_

#include "token.h"

#define MAX_STACK_SIZE 100
struct stack {
    struct token storage[MAX_STACK_SIZE];
    int top;
};

void stack_init(struct stack *stack);

void stack_push(struct stack *stack, struct token token);

struct token stack_top(struct stack *stack);

struct token stack_pop(struct stack *stack);

void stack_dump(struct stack *stack);

#endif  //  SRC_SUPERCALC_SIMPLE_STACK_H_
