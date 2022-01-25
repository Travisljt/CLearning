#pragma once

#include "../General/general.h"
#include "../Include/var.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct stack stack;

/* Create an empty stack */
stack *stack_init(void);
/* Add element to top */
void stack_push(stack *s, Variable v);
/* Take element from top */
bool stack_pop(stack *s, Variable *v);
/* Clears all space used */
bool stack_free(stack *s);
