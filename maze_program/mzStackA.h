/* Note.
	Stack is implemented by using an array.
*/  
#ifndef	_MAZE_STACK
#define	_MAZE_STACK
#ifndef	_MAZE_STACK_
#define	_MAZE_STACK_

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

#define	MAX_MAZE_STACK_SIZE	10000

typedef	struct	{
	int xx;		// x-axis of the current position
	int yy;		// y-axis of the current position
	int dir;	// next search direction
} mazeStackElement_t;

typedef	struct	{
	int	top;
	mazeStackElement_t	elements[MAX_MAZE_STACK_SIZE];
} mazeStack_t;

void	mazeStack_init(mazeStack_t *stack);
int	mazeStack_full(mazeStack_t *stack);
int	mazeStack_empty(mazeStack_t *stack);
int	mazeStack_insert(mazeStack_t *stack, mazeStackElement_t *element);
int	mazeStack_delete(mazeStack_t *stack, mazeStackElement_t *element);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* _MAZE_STACK_ */
#endif	/* _MAZE_STACK */

