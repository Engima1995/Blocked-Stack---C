#ifndef STACK_int_H
#define STACK_int_H

typedef struct stack_int_implementation stack_int;

stack_int * new_blocked_stack_int(int block_size);
int stack_int_isempty(stack_int *s);
int stack_int_size(stack_int *s);
void stack_int_push(stack_int *s, int x);
void stack_int_pop(stack_int *s);
int stack_int_top(stack_int *s);
void stack_int_display(stack_int *s);
void stack_int_release(stack_int *s);

#endif
