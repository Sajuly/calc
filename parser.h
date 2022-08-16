#ifndef SRC_SUPERCALC_PARSER_H_
#define SRC_SUPERCALC_PARSER_H_

#include "simple_list.h"

#define MAX_LEXEMA_LENGTH 255

#ifdef __cplusplus
#define EXTERNC extern "C"  //  говорит компилятору что написано на С
#else
#define EXTERNC
#endif

EXTERNC struct list parse_source(char *source);

EXTERNC int check_parse_errors(struct list *parsed_list);

#endif  //  SRC_SUPERCALC_PARSER_H_
