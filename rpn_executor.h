#ifndef SRC_SUPERCALC_RPN_EXECUTOR_H_
#define SRC_SUPERCALC_RPN_EXECUTOR_H_

#include "simple_list.h"

#ifdef __cplusplus
#define EXTERNC extern "C"  // говорит компилятору что написано на С
#else
#define EXTERNC
#endif

EXTERNC struct list rpn(struct list *parsed_list);

EXTERNC double executor(struct list *rpn, double x);

#endif  //  SRC_SUPERCALC_RPN_EXECUTOR_H_
