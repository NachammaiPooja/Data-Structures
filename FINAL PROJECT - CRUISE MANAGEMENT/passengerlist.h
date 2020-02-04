#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

typedef struct dett
{
	char name[100];
	char gender;
	int age;
	char proof[50];
	char Class[50];
	char src[50];
	char dest[50];
}details;

struct Node
{
	 
	 details det;
	 Position Next;
	 Position Prev;

};


List CreateEmptyList()
{
	List t,h;
	h=(List)malloc(sizeof(struct Node));
	t=(List)malloc(sizeof(struct Node));
	h->Prev=NULL;
	h->Next=t;
	t->Prev=h;
	t->Next=NULL;
	return h;
}


int IsEmpty( List L )
{
	 return L->Next == NULL;
}
int Find(List L,char X[])
{
 	 int i=1;
	 Position P;
	 P = L->Next;
	 while( (P->Next) != NULL && strcmp(P->det.name,X)!=0 )
	 {
	 P = P->Next;
	 i++;	
	 }
	 
 	 if(P->Next == NULL){
 	 	printf("No name found.\n");
		return -1;
	}
 	else
 	{

 	 printf(" Name is in position %d\n",i);
 	 printf("Name:%s\n",P->det.name);
 	 printf("Gender:%c\n",P->det.gender);
 	 printf("Age:%d\n",P->det.age);
 	 printf("Proof:%s\n",P->det.proof);
 	 printf("Class:%s\n",P->det.Class);
	}
	return 1;

}


void addend(List L, details d)
{
 	Position Temp,P;
 	int i;
 	P=L;
 	while(P->Next!=NULL)
 		{
 			P=P->Next;
 		}
 	P=P->Prev;
 	Temp =(List) malloc( sizeof( struct Node ) );
 	Temp->det=d;
 	Temp->Next = P->Next;
 	Temp->Prev = P;
 	Temp->Next->Prev=Temp;
 	P->Next=Temp;

}

void Delete(List L, char X[])
{
	Position P,temp;
	P = L->Next;
    while( P!= NULL && (strcmp(P->det.name,X)!=0) )
	{
	P = P->Next;	
	}
	if(P!=NULL)
	{
	temp = P;
	temp -> Next -> Prev = temp -> Prev;
	temp -> Prev -> Next = temp -> Next;
	free(temp);
	}
	else
		printf("\n%s is not present in the list\n", X);
}

void disp(List h)
{
	List temp;
	temp=(List)malloc(sizeof(struct Node));
	temp=h->Next;
	printf("All records.\n");
	while(temp->Next!=NULL)
	{
		printf("\n%s",temp->det.name);
		temp=temp->Next;
	}
	printf("\n");
}

void checkavailabilty(char a[])
{
	FILE *fptr;
	fptr=fopen("today.txt","r");
	char c[10];
	int i,j=1,k=1,co=0,co1=0;
	for(i=0;i<10;i++)
	{
		fscanf(fptr,"%s",c);
		{
			if(c[1]<65)
			{
				a[j]=c[0];
				j++;
				co++;
			}
		}
	}
	fclose(fptr);
	while(j<10)
	{
		a[j]='\0';
		j++;
	}
	if(co==0) a[0]='n';	
	else a[0]='y';
	return;
}

