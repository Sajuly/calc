#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include "rpn_executor.h"
#include "simple_list.h"
#include "token.h"
#include "simple_stack.h"

/*
{'_', 10, ASSOC_RIGHT, 1, eval_uminus},
{'^', 9,  ASSOC_RIGHT, 0, eval_exp},
{'*', 8,  ASSOC_LEFT,  0, eval_mul},
{'/', 8,  ASSOC_LEFT,  0, eval_div},
{'%', 8,  ASSOC_LEFT,  0, eval_mod},
{'+', 5,  ASSOC_LEFT,  0, eval_add},
{'-', 5,  ASSOC_LEFT,  0, eval_sub},
{'(', 0,  ASSOC_NONE,  0, NULL},
{')', 0,  ASSOC_NONE,  0, NULL}
 */

struct list rpn(struct list *parsed_list) {
    // приоритет операций по типам токенов от TT_END до TT_UNKNOWN
    const int precedence[23] = {0, 0, 2, 2, 4, 4, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 5, 4, 6, 6, 0};

    struct stack stack;
    struct list result;

    struct token current_tt, top_tt;

    stack_init(&stack);
    list_init(&result);

    current_tt = list_get_first(parsed_list);
    while (current_tt.token_type != TT_END) {
        switch (current_tt.token_type) {
            case TT_DIGIT:
            case TT_X:
                list_append(&result, current_tt);
                break;
            case TT_SIN:
            case TT_COS:
            case TT_TAN:
            case TT_ASIN:
            case TT_SQRT:
            case TT_LN:
            case TT_ACOS:
            case TT_ATAN:
            case TT_LOG:
                stack_push(&stack, current_tt);
                break;
            case TT_PLUS:
            case TT_MINUS:
            case TT_MUL:
            case TT_DIV:
            case TT_POW:
            case TT_MOD:
            case TT_U_MINUS:
            case TT_U_PLUS:
                top_tt = stack_top(&stack);
                while ((top_tt.token_type != TT_END) && (top_tt.token_type != TT_OPEN_BRACKET)
                       && (precedence[top_tt.token_type] >= precedence[current_tt.token_type])) {
                    list_append(&result, stack_pop(&stack));
                    top_tt = stack_top(&stack);
                }

                stack_push(&stack, current_tt);
                break;
            case TT_OPEN_BRACKET:
                stack_push(&stack, current_tt);
                break;
            case TT_CLOSE_BRACKET:
                top_tt = stack_top(&stack);
                while (top_tt.token_type != TT_OPEN_BRACKET) {
                    if (top_tt.token_type == TT_END) {
                        printf("Absent open bracket\n");
                        abort();
                    }
                    list_append(&result, stack_pop(&stack));
                    top_tt = stack_top(&stack);
                }
                if (top_tt.token_type != TT_OPEN_BRACKET) {
                    printf("Absent open bracket\n");
                    abort();
                }
                stack_pop(&stack);
                top_tt = stack_top(&stack);
                switch (top_tt.token_type) {
                    case TT_SIN:
                    case TT_COS:
                    case TT_TAN:
                    case TT_ASIN:
                    case TT_ACOS:
                    case TT_ATAN:
                    case TT_LOG:
                    case TT_SQRT:
                    case TT_LN:
                        list_append(&result, stack_pop(&stack));
                        break;
                }

                break;
            default:
                break;
        }
        current_tt = list_get_next(parsed_list);
    }

    current_tt = stack_pop(&stack);
    while (current_tt.token_type != TT_END) {
        list_append(&result, current_tt);
        current_tt = stack_pop(&stack);
    }

    return result;
}

double executor(struct list *rpn, double x) {
    double result;

    struct stack stack;
    stack_init(&stack);

    struct token current_tt, a, b;
    struct token val = {TT_DIGIT, 0, "0"};
    struct token x_tt = {TT_DIGIT, x, ""};

    current_tt = list_get_first(rpn);
    while (current_tt.token_type != TT_END) {
        switch (current_tt.token_type) {
            case TT_DIGIT:
                stack_push(&stack, current_tt);
                break;
            case TT_X:
                stack_push(&stack, x_tt);
                break;
            case TT_SIN:
                a = stack_pop(&stack);
                val.value = sin(a.value);
                stack_push(&stack, val);
                break;
            case TT_COS:
                a = stack_pop(&stack);
                val.value = cos(a.value);
                stack_push(&stack, val);
                break;
            case TT_TAN:
                a = stack_pop(&stack);
                val.value = tan(a.value);
                stack_push(&stack, val);
                break;
            case TT_ASIN:
                a = stack_pop(&stack);
                val.value = asin(a.value);
                stack_push(&stack, val);
                break;
            case TT_ACOS:
                a = stack_pop(&stack);
                val.value = acos(a.value);
                stack_push(&stack, val);
                break;
            case TT_ATAN:
                a = stack_pop(&stack);
                val.value = atan(a.value);
                stack_push(&stack, val);
                break;
            case TT_SQRT:
                a = stack_pop(&stack);
                val.value = sqrt(a.value);
                stack_push(&stack, val);
                break;
            case TT_LN:
                a = stack_pop(&stack);
                val.value = log(a.value);
                stack_push(&stack, val);
                break;
                // operators
            case TT_LOG:
                a = stack_pop(&stack);
                val.value = log10(a.value);
                stack_push(&stack, val);
                break;
                // operators
            case TT_PLUS:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                val.value = a.value + b.value;
                stack_push(&stack, val);
                break;
            case TT_MOD:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                val.value = fmod(b.value, a.value);
                stack_push(&stack, val);
                break;
            case TT_MINUS:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                val.value = b.value - a.value;
                stack_push(&stack, val);
                break;
            case TT_MUL:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                val.value = a.value * b.value;
                stack_push(&stack, val);
                break;
            case TT_POW:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                val.value = pow(b.value, a.value);
                stack_push(&stack, val);
                break;
            case TT_U_MINUS:
                a = stack_pop(&stack);
                val.value = 0 - a.value;
                stack_push(&stack, val);
                break;
            case TT_U_PLUS:
                a = stack_pop(&stack);
                val.value = 0 + a.value;
                stack_push(&stack, val);
                break;
            case TT_DIV:
                a = stack_pop(&stack);
                b = stack_pop(&stack);
                if (b.value != 0.0) {
                    val.value = b.value / a.value;
                } else {
                    val.value = 100000;
                }
                stack_push(&stack, val);
                break;
        }
        current_tt = list_get_next(rpn);
    }

    current_tt = stack_top(&stack);
    result = current_tt.value;

    return result;
}
