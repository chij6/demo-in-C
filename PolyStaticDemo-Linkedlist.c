#include<stdio.h>
#include<stdlib.h>
#define COMPARE(x, y) (((x) < (y))? -1 : ((x) == (y)) ? 0 : 1 )
#define insert() linkedList_insert()

polyPointer a,b;
int a_size,b_size;

polyPointer insert(int polySize);
polyPointer padd(polyPointer a,polyPointer b);
void printPoly(polyPointer first);
void attach(float coef,int expon,polyPointer *ptr);

int main(int argc,const char* argv){
	
	int i;
	scanf("%d",&a_size);
	scanf("%d",&b_size);

	a=insert(a_size);
	b=insert(b_size);
	
	printf("a(x)= ");
	printPoly(a);
	printf("b(x)= ");
	printPoly(b);
	printf("c(x)= ");
	printPoly(padd(a,b));
}
 
void printPoly(polyPointer first)
{
    printf("%.1fx^%d", first->coef, first->expon);
	first = first->link;
	for( ;first;first = first->link)
		printf("%+.1fx^%d", first->coef, first->expon);
	printf("\n");
}

polyPointer padd(polyPointer a ,polyPointer b)
{	
    polyPointer polyC, rear ,temp;
    int sum;
    rear = (polyPointer)malloc(sizeof(rear));
    polyC = rear;
    while(a && b)
           switch(COMPARE(a->expon,b->expon))
		   {
                  case -1:
                          attach(b->coef, b->expon, &rear);
                          b = b->link;
                          break;
                  case 0:
                          sum = a->coef + b->coef;
                          if(sum) 	attach(sum ,a->expon ,&rear);
							a = a->link;
							b = b->link;
                           break;
                  case 1:
                           attach(a->coef, a->expon, &rear);
                           a = a->link;
          }
    for( ; a ; a=a->link)
         attach(a->coef, a->expon, &rear);

    for( ; b ; b=b->link)
         attach(b->coef, b->expon, &rear);
    rear->link = NULL;
    
    temp=polyC;
    polyC = polyC->link;
    free(temp);
    return polyC;
}

void attach(float coef,int expon,polyPointer *ptr)
{
    polyPointer temp;
    temp = (polyPointer)malloc(sizeof(temp));
    temp->coef = coef;
    temp->expon = expon;
    (*ptr)->link=temp;
    *ptr = temp;
}
