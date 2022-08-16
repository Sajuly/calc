#include <stdio.h>
#include <stdlib.h>
#include "simple_list.h"

void list_init(struct list *list) {
    list->current = 0;
    list->count = 0;
}
struct token list_get_first(struct list *list) {
    list->current = 0;
    return list->storage[list->current];
}
struct token list_get_next(struct list *list) {
    if (list->current + 1 >= list->count) {
        struct token end_list = {TT_END, 0, ""};
        return end_list;
    }
    list->current++;
    return list->storage[list->current];
}

void list_append(struct list *list, struct token token) {
    list->storage[list->count] = token;
    list->count++;
}

void list_debug_print(struct list *list) {
    struct token tt = list_get_first(list);
    while (tt.token_type != TT_END) {
        printf("type:%d value:%lf str:%s\n", tt.token_type, tt.value, tt.string);
        tt = list_get_next(list);
    }
}
