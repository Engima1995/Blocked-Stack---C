#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "blocked_stack_int.h"

char line[] = "****************************************";

void snapshot(stack_int * s, char * m)
{
	printf("\n%s\n", line);
	printf("** %s\n", m);

	printf("** Stack size   is %4i\n", stack_int_size(s));
	if (!stack_int_isempty(s))
		printf("** Top of stack is %4i\n", stack_int_top(s));
	printf("%s\n", line);
	stack_int_display(s);
}

int main()
{

	int i,j;
	int bs=10;

	stack_int * s = new_blocked_stack_int(bs);
	snapshot(s, "New stack");

	printf("Pushing and popping. All ok: ");
	j = bs*2+2;
	for(i=0; i<j; i++)
		stack_int_push(s, i);
	for(i=j-1; i>=0; i--)
	{
		if (i != stack_int_top(s))
		{
			printf("NO!\n");
			exit(1);
		}
		stack_int_pop(s);
	}
	printf("YES\n");

	printf("Stack should be empty: ");
	if (stack_int_isempty(s))
		printf("YES\n");
	else
	{
		printf("NO!\n");
		exit(1);
	}

	stack_int_push(s, 1);
	snapshot(s, "Pushed an item");

	for(i=2;i<=bs;i++) stack_int_push(s, i);
	snapshot(s, "Filled first block");

	stack_int_push(s, 11);
	snapshot(s, "Push an item - created new block");

	for(i=bs+2;i<=3*bs-1;i++) stack_int_push(s, i);
	snapshot(s, "Created two new blocks");

	stack_int_push(s, 3*bs);
	snapshot(s, "Pushed an item filling the block");

	stack_int_push(s, 3*bs+1);
	snapshot(s, "Pushed an item creating new block");

	stack_int_pop(s);
	snapshot(s, "Popped an item - lose one block");

	stack_int_pop(s);
	snapshot(s, "Popped an item");

	for(i=1;i<bs;i++) stack_int_pop(s);
	snapshot(s, "Popped items - clearing the first block");

	for(i=1;i<bs+bs/2;i++) stack_int_pop(s);
	snapshot(s, "Popped items - cleared one and a half blocks");

	while (stack_int_size(s) > 1) stack_int_pop(s);
	snapshot(s, "Emptied the stack bar one element");

	stack_int_pop(s);
	snapshot(s, "Popped the last item");

	return 0;
}
