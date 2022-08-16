#include <stdlib.h>
#include <stdio.h>
#include "simple_stack.h"

void stack_init(struct stack *stack) {
    stack->top = 0;
}

void stack_push(struct stack *stack, struct token token) {
    if (stack->top + 1 >= MAX_STACK_SIZE) {
        printf("Stack overflow");
        abort();
    }
    stack->top++;
    stack->storage[stack->top] = token;
}
struct token stack_top(struct stack *stack) {
    if (stack->top == 0) {
        struct token empty_stack = {TT_END, 0, ""};
        return empty_stack;
    }

    return (*stack).storage[(*stack).top];
}
struct token stack_pop(struct stack *stack) {
    if (stack->top == 0) {
        struct token empty_stack = {TT_END, 0, ""};
        return empty_stack;
    }
    stack->top--;
    return stack->storage[stack->top + 1];
}

void stack_dump(struct stack *stack) {
    struct token tkn2 = stack_pop(stack);
    while (tkn2.token_type != TT_END) {
        printf("type:%d value:%lf str:%s\n", tkn2.token_type, tkn2.value, tkn2.string);
        tkn2 = stack_pop(stack);
    }
}
