#include<stdio.h>
#include<stdlib.h>
#define COMPARE(x, y) (((x) < (y))? -1 : ((x) == (y)) ? 0 : 1 )
typedef struct{
              	int expon;
              	float coef;
              }polynomial;

int total,size1,size2;
int startA, finishA, startB, finishB;
int startD,finishD,avail=0;
              
void printPoly(polynomial arr[],int i,int x);
void padd(int startA, int finishA, int startB, int finishB, polynomial arr[]);
void attach(int coef, int expon, polynomial result[]);
void printResult(polynomial result[]);


int main(int argc,const char* argv){
	
	int i=0;
	scanf("%d",&size1);
	scanf("%d",&size2);
	total=size1+size2;
	polynomial *arr = calloc(total,sizeof(polynomial));
	
	startA=0;
	finishA=size1-1;
	startB=size1;
	finishB=total-1;

	if(arr == NULL){
		fprintf(stderr,"ERROR : Required memory can't be allocate!!!\n");
		return ;
	}
	while(i < total){
		scanf("%f,%d",&arr[i].coef,&arr[i].expon);
		i++;
	}
	printf("a(x)= ");
	printPoly(arr,startA,finishA);
	printf("b(x)= ");
	printPoly(arr,startB,finishB);
	
	padd(startA, finishA, startB, finishB, arr);
		
	free(arr);
}

void printPoly(polynomial arr[], int i, int x)
{
    printf("%.1fx^%d", arr[i].coef, arr[i].expon);
    i =  i + 1;
	for( ; i <= x ; i++)
	    printf("%+.1fx^%d", arr[i].coef, arr[i].expon);
	printf("\n");
}

void printResult(polynomial result[])
{
    int i = startD;
    printf("d(x)= ");
    printf("%.1fx^%d", result[i].coef, result[i].expon);
    i =  i + 1;
    for( ; i <= finishD ; i++)
	    	printf("%+.1fx^%d", result[i].coef, result[i].expon);
	printf("\n");
}

void padd(int startA, int finishA, int startB, int finishB, polynomial arr[])
{	
    int coef;
    startD = avail;
    polynomial *result = calloc(total,sizeof(polynomial));
    while((startA <= finishA) && (startB <= finishB))
           switch(COMPARE(arr[startA].expon, arr[startB].expon))
		   {
                  case -1:
                          attach(arr[startB].coef, arr[startB].expon,result);
                          startB++;
                          break;
                  case 0:
                          coef = arr[startA].coef + arr[startB].coef;
                          if(coef) attach(coef,arr[startA].expon,result);
                             startA++;
                             startB++;
                           break;
                  case 1:
                           attach(arr[startA].coef, arr[startA].expon,result);
                           startA++;
          }
    for( ; startA <= finishA ; startA++)
         attach(arr[startA].coef, arr[startA].expon,result);

    for( ; startB <= finishB ; startB++)
         attach(arr[startB].coef, arr[startB].expon,result);
    
    finishD = avail - 1;
    
    printResult(result);
    free(result);
}

void attach(int coef, int expon, polynomial result[])
{
     if(avail >= total)
	 {
         fprintf(stderr, "Too many terms!\n");
         return ;
     }
     result[avail].coef    = coef;
     result[avail++].expon = expon;
}
