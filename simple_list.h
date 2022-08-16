#ifndef SRC_SUPERCALC_SIMPLE_LIST_H_
#define SRC_SUPERCALC_SIMPLE_LIST_H_

#include "token.h"

#ifdef __cplusplus
#define EXTERNC extern "C"  // говорит компилятору что написано на С
#else
#define EXTERNC
#endif


#define MAX_LIST_SIZE 256
struct list {
    struct token storage[MAX_LIST_SIZE];
    int current;
    int count;
};

void list_init(struct list *list);

struct token list_get_first(struct list *list);

struct token list_get_next(struct list *list);

void list_append(struct list *list, struct token token);

EXTERNC void list_debug_print(struct list *list);

#endif  //  SRC_SUPERCALC_SIMPLE_LIST_H_
