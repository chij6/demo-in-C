#include "mzStackA.h"

//stack ADT 

void mazeStack_init(mazeStack_t *stack) 
{
	stack -> top = -1;
}

int mazeStack_full(mazeStack_t *stack)
{
	return (stack->top >= (MAX_MAZE_STACK_SIZE - 1));	
}

int mazeStack_empty(mazeStack_t *stack) 
{
	return (stack->top  == -1);
}

int mazeStack_insert(mazeStack_t *stack, mazeStackElement_t *element) 
{
	if (mazeStack_full(stack)) {
		return 0;
	} else {
		stack->elements[++(stack->top)] = *element;
		return 1;
	}
}

int mazeStack_delete(mazeStack_t *stack, mazeStackElement_t *element) 
{
	if (mazeStack_empty(stack)) {
		return 0;
	} else {
		*element = stack->elements[(stack->top)--];
		return 1;
	}
}
