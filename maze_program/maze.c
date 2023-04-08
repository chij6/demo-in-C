#include<stdio.h>
#include "mzStackA.h"
#define	JWD(x) printf x

/*	Data Structures and Interface of MAZE	*/

struct	{
	int off_x;
	int off_y;
} offsets[4] = {
	{ -1,  0 },	// N, North
	{  0,  1 },	// E, East
	{  1,  0 },	// S, South
	{  0, -1 }	// W, West
};


#define	DIRS	(sizeof(offsets)/sizeof(offsets[0]))    // 32/8 
#define	ENDPT	(DIRS+0)  								//4
#define	SPACE	(DIRS+1)  								//5
#define	WALL	(DIRS+2)  								//6

char *display[] = { "^", ">", "v", "<", "*", " ", "H" };

#define	VISITED	'Y'
#define	NON_VISITED	'N'
#define	MAX_MAZE_SIZE	100
#define	MAX_ARRAY_SIZE	(MAX_MAZE_SIZE + 2)


int	mm;
int	nn;
int	 maze[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
char mark[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];


void	mazeInit();
int mazeIsSpace(int xx, int yy);
int mazeIsVisited(int xx, int yy);
int mazeMarkVisited(int xx, int yy);
int mazeMarkPath(int xx, int yy, int dir);

/*	Data Structure and Interface of STACK	*/

mazeStack_t	myStack;

#define	stack_init()	mazeStack_init(&myStack)
#define	stack_full()	mazeStack_full(&myStack)
#define	stack_empty()	mazeStack_empty(&myStack)
#define	push(element)	mazeStack_insert(&myStack, (element))
#define	pop(element)	mazeStack_delete(&myStack, (element))

/*	Others	*/
void ShowMaze();
int	 ReadFile(FILE *file);
int	 FindPath();
int	 Rollback();

/*	Main Function	*/
int main(int argc, char *argv[]){

	FILE	*input = NULL;
	if (argc < 2) {
		input = stdin;
	} else {
		input = fopen(argv[1], "rt");
		if (input == NULL) {
			JWD(("file [%s] not found\n", argv[1]));
			return 1;
		}
	}
	
	mazeInit();
	
	if (ReadFile(input) == 0) {
		JWD(("read file [%s] error\n", argv[1]));
		return 1;
	}
	
	ShowMaze();

	printf("search a path from (1,1) to (%d,%d)...\n", mm, nn);
	if (FindPath() == 0) {
		JWD(("path is not found\n\n"));
		return 1;
	}
	JWD(("path is found\n\n"));
	
	ShowMaze();
}

int FindPath()
{
	//Set initial value & check value
	mazeStackElement_t now, next;    
	now.xx = 1;
	now.yy = 1;
	now.dir = 0;

	stack_init(); 
	push(&now);         
	
	while (! stack_empty()) 
	{
		pop(&now);     
		JWD(("back to (%d, %d)\n", now.xx, now.yy));
		for (;now.dir<4; now.dir++) 
		{
			//Next Direction 
		    next.xx = now.xx + offsets[now.dir].off_x; 
		    next.yy = now.yy + offsets[now.dir].off_y;
		    
			//Find the right Direction 
			JWD(("test (%d,%d)\n", next.xx, next.yy));
			if (mazeIsSpace(next.xx, next.yy) &&  (!mazeIsVisited(next.xx, next.yy)) ) 
			{
				mazeMarkVisited(next.xx, next.yy);
				push(&now);
				JWD(("move to (%d, %d)\n", next.xx, next.yy)); 
				now.xx = next.xx;
				now.yy = next.yy;
				now.dir = -1;
				
				if ((now.xx == mm) && (now.yy == nn)) 
				{
					mazeMarkPath(now.xx, now.yy, ENDPT);
					Rollback();
					return 1;
				}
			}
		}
	}
	return 0;
}

int Rollback()
{
	mazeStackElement_t stop;
	JWD(("Stack: \n"));

	while (! stack_empty()) {
		pop(&stop);
		JWD(("(%d, %d, %d)\n", stop.xx, stop.yy, stop.dir));
		mazeMarkPath(stop.xx, stop.yy, stop.dir);
	}
	return 1;
}

/*	MAZE relation operations	*/

int ReadFile(FILE *file)
{
	int ii, jj;
	if (fscanf(file, "%d,%d", &mm, &nn) < 2) {
		return 0;
	}
	for (ii=1; ii<=mm; ii++) {
		for (jj=1; jj<=nn; jj++) {
			int digit;
			if (fscanf(file, "%d", &digit) < 1) {
				return 0;
			}
			if (digit == 0) {
				maze[ii][jj] = SPACE;
			}
		}
	}
	return 1;
}

void ShowMaze() 
{
	int  i,j;
	JWD(("MAZE SIZE: %dx%d\n",mm,nn));
	for(i=0;i <= mm+1;i++){
		for(j=0; j<= nn+1;j++){
			JWD(("%c",*display[maze[i][j]]));
		}
	printf("\n");
	}
}

void mazeInit() 
{
	int ii, jj;
	for (ii=0; ii<MAX_ARRAY_SIZE; ii++) {
		for (jj=0; jj<MAX_ARRAY_SIZE; jj++) {
			maze[ii][jj] = WALL;
			mark[ii][jj] = NON_VISITED;
		}
	}
}

int mazeIsSpace(int xx, int yy) 
{
	 if(maze[xx][yy] == SPACE) return 1;
	 else return 0;
}

int mazeIsVisited(int xx, int yy)         //Whether it has already visited or not
{
	if(mark[xx][yy] == NON_VISITED) return 0;
	else return 1;
}

int mazeMarkVisited(int xx, int yy)	  // Marked the past way
{
	mark[xx][yy] = VISITED;
	return 1;
}

int mazeMarkPath(int xx, int yy, int dir) //Finished new maze 
{
	(xx == mm && yy == nn)  ? (maze[xx][yy] = ENDPT) : (maze[xx][yy] = dir);
	return 1;
}
