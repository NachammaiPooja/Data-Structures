#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include"passengerlist.h"
#include "graph.h"

typedef struct
{
	char source;
	char destination;
}route;

typedef struct mynode
{
	char room[25];
	struct mynode *next;
}node;


void displaystations()
{
	printf("Stations : \n");
	for(int i=0;i<5;i++)
	{
		printf("%d ) %s\n",i,p[i]);
	}
}

int findindex(char str[])
{
	for(int i=0;i<5;i++)
	{
		if(!strcmp(p[i],str))
			return i;
	}
	return -1;
}

void update(node *a,char c[20])
{
	FILE *fptr;
	node *temp;
	temp=a;
	fptr=fopen(c,"w");
	while(temp->next!=NULL)
	{
		fprintf(fptr,"%s\n",temp->room);
		temp=temp->next;
	}
	fclose(fptr);
}


/*void Book(List L)
{
	printf("WELCOME.\n");
	details det;
	int num;
	char a[50];
	char src[100],dest[100];
	printf("Enter your details as follows.\n");
	printf("Enter the number of tickets:");
	scanf("%d",&num);
	for(int i=0;i<num;i++)
	{

		printf("Enter name:");
		scanf("%s",det.name);
		printf("Enter gender(M/F/T):");
		scanf(" %c",&det.gender);
		printf("Enter age:");
		scanf("%d",&det.age);
		printf("Enter proof of identity:");
		scanf("%s",det.proof);
		printf("Enter class(First/Second/Sleeper):");
		scanf("%s",det.Class);
		printf("Enter the boarding station:");
		scanf("%s",src);
		printf("Enter the destination:");
		scanf("%s",dest);
		addend(L,det);
	}
	printf("Ticket cost:"); 
	printf("Afterwards \n");
}*/

void Status(List L)
 
{
	char name[100];
	printf("Enter the name to know status:");
	scanf("%s",name);
	int i=-1;
	printf("\tDetails");
	i=Find(L,name);
	if(i!=-1)
	{
		printf("Status:Your tickets are confirmed.\n");
	}
	else
		printf("Status: You have no confirmed booking\n");
}

void Chart()
{
	printf("Reservation of rooms.\n");
	int i=1;
	int x=0;
	FILE *fptr;
	char b1[20],a1[20];
	fptr=fopen("today.txt","r");
	for(i=0;i<10;i++)
	{	
		x=0;
		fscanf(fptr,"%s",b1);
		while(b1[x]!='\0'){
			a1[x-1]=b1[x];	
			x++;
		}
		a1[x-1]='\0';
		while(a1[0]!='\0'){
		printf("\nName : %s Room : %c",a1,b1[0]); 
		break;
		}	
	}
	fclose(fptr);
}

void Routes(int G[][5])
{
	int fs[5],size;
	int ch=1;
	char Start[50];
	int start;
	while(ch!=0)
	{
		printf("\n\n\t\t1.Cruise Set Path\n\t\t2.Possiible Routes from selected Port\n\t\t0.Exit\n\t\tEnter Choice : ");
		scanf(" %d",&ch);
		switch(ch)
		{
			case 1 :
					displaystations();
					printf("\nEnter Boarding Station : ");
					scanf("%d",&start);
					size=0;
					size=dfs(start,G,fs,size);
					printf("DFS : \n");
					for(int i=0;i<5;i++)
						printf("-->%s --",p[fs[i]]);
					printf("\n");
					break;
			/*case 1 :
					displaystations();
					printf("\nEnter Boarding Port : ");
					scanf("%d",&start);
					size=0;
					size=bfs(start,G,fs,size);
					printf("BFS : \n");
					for(int i=0;i<5;i++)
						printf("%s ",p[fs[i]]);
					printf("\n");
					break;*/
			case 2 :
					printf("\nAll available Boarding Port : ");
					displaystations();
					printf("\nEnter Boarding Port : ");
					scanf("%d",&start);
					dijkstra(G,5,start);
					break;
			case 0 : break;
			default : printf("Invalid Choice \n");
		}
	}
}
node* insert1()
{
	FILE *fptr;
	node *p,*head,*temp;
	int i,j=0;
	char ch[20];
	fptr=fopen("today.txt","r");
	p=(node*)malloc(sizeof(node));
	head=p;
	for(i=0;i<10;i++)
	{
		fscanf(fptr,"%s",ch);
		strcpy(p->room,ch);
		temp=(node*)malloc(sizeof(node));
		p->next=temp;
		p=p->next;
	}
	fclose(fptr);
	return head;
}

node* cancel_1(node *a,char b[],int c)
{
	int i;
	node *temp;
	char ch[20];
	for(i=0;i<c;i++)
	{
		temp=a;
		while(temp->next!=NULL)
		{
			if(temp->room[0]==b[i])
			{
				ch[0]=temp->room[0];
				strcpy(temp->room,ch);
				break;
			}
			else temp=temp->next;
		}
	}
	return a;
}
void cancel(char a[])
{
	FILE *fptr;
	int i,j=0,n,t=0,l,t1;
	char ch[25],c1[25],se,li[25],c[25];
	node *p;
	fptr=fopen("today.txt","r");
	for(i=48;i<58;i++)
	{
		ch[0]=i;
		for(t1=1;t1<25;t1++) ch[t1]='\0';
		fscanf(fptr,"%s",c);
		strcat(ch,a);
		if((strcmp(c,ch))==0)
		{
			printf("%s",ch);
			c1[j]=c[0];
			j++;
			
		}
	}
	printf("%d",j);
	fclose(fptr);
	if(c1[0]=='\0') printf("\nYou don't have any booking on this date\n");
	else
	{
		printf("\nRoom booked by you\n");
		for(i=0;i<j;i++) printf("%c ",c1[i]);
		printf("\nkindly select no of rooms you want to cancel\n");
		j=1;
		do
		{
			scanf("%d",&n);
			if(n<=strlen(c1)) j=0;
			else printf("\nkindly select correct no of rooms\n");
		}while(j);
		for(j=0;j<n;j++)
		{
			printf("room-%d:",j+1);
			scanf("\n%c",&se);
			for(l=0;l<strlen(c1);l++)
			{
				if(c1[l]==se) break;
			}
			if(l<strlen(c1))
			{
				li[t]=se;
				t++;
			}
			else 
			{
				printf("kindly select rooms booked by you\n");
				j--;
			}
		}
		p=insert1();
		p=cancel_1(p,li,t);
		update(p,"today.txt");
		
	}
}


node* book_1(node* a,char b[],char c[],int d)
{
	int i;
	node *temp;
	FILE *fptr;
	for(i=0;i<d;i++)
	{
		temp=a;
		while(temp->next!=NULL)
		{
			if(temp->room[0]==b[i])
			{
				strcat(temp->room,c);
				break;
			}
			else temp=temp->next;
		}
	}
	return a;
}

void payment(int a,int n)
{
	int age,fare,tax,i;
	char ca[20],cv[20],ot[20],ch[20];
	if(a==1) fare = 50000;
	else if(a==2) fare = 20000;
	else fare = 10000;
        tax=(0.2*fare);
	printf("\nCruise Fare Summary\n\n"); 
	printf("\nPer Family:\n");	
	printf("Cruise Fare\t\t%d\n",fare);
	printf("Taxes   \t\t%d\n",tax);
	printf("Total   \t\t%d\n",fare+tax);
	printf("\n\nTotal Cruise Fare\t\t%d.00\n",((fare+tax)*n));
	printf("\nPAYMENT GATEWAY\n");
	printf("\nEnter 1-Debit card/2-Credit card/3-Netbanking/4-UPI\n");
	scanf("%d",&i);
	printf("\n");
	if(i==1)
	{
		printf("\nEnter card number:");
		scanf("\n%s",ca);
		printf("\nEnter cvv number:");
		scanf("\n%s",cv);
		printf("\nRedirecting to payment portal\n");
		printf("\nEnter OTP:");
		scanf("\n%s",ot);
		printf("\nPayment Processing\n");
	}
	else if(i==2)
	{
		printf("\nEnter card number:");
		scanf("\n%s",ca);
		printf("\nEnter cvv number:");
		scanf("\n%s",cv);
		printf("\nRedirecting to payment portal\n");
		printf("\nEnter OTP:");
		scanf("\n%s",ot);
		printf("\nPayment Processing\n");
	}
	else if(i==3)
	{
		printf("\nEnter username:");
		scanf("\n%s",ca);
		printf("\nEnter password:");
		scanf("\n%s",cv);
		printf("\nRedirecting to payment portal\n");
		printf("\nEnter OTP:");
		scanf("\n%s",ot);
		printf("\nPayment Processing\n");
	}
	else
	{
		printf("\nEnter UPI password:");
		scanf("\n%s",ca);
		printf("\nEnter UPI pin:");
		scanf("\n%s",cv);
		printf("\nPayment Processing\n");
	}
	printf("\nPayment Successful\n");
	printf("\nTickets have been booked successfully\n\n");
	printf("Thankyou for choosing us\n");
	printf("Wish You A Safe And Happy Journey\n");
	return;
}	
void Cancel1(List L)
{
	printf("\nEnter the name of Person on ticket to cancel");
	char name[100];
	scanf("%s",name);
	Delete(L,name);
	cancel(name);
	printf("\nCancelled ticket successfully.\n");
}
/*void update(node *a,char c[20])
{
	FILE *fptr;
	node *temp;
	temp=a;
	fptr=fopen(c,"w");
	while(temp->next!=NULL)
	{
		fprintf(fptr,"%s\n",temp->room);
		temp=temp->next;
	}
	fclose(fptr);
}*/

void Book(List L)
{
	char a[30];
	checkavailabilty(a);
	details det;
        printf("\nAvailable rooms\n");
	for(int l=1;l<strlen(a);l++)
	{
		printf("%c  ",a[l]);
	}
	node *p,*p1;
	int j,l,i=0,n;
	char li[20],c1[20],se;
	printf("\nKindly select no of Rooms\n");
	j=1;
	do
	{
		scanf("%d",&n);
                getchar();
		if(n<strlen(a)) j=0;
		else printf("\nKindly select correct no of Rooms\n");
	}while(j);
	printf("\nKindly select your room\n");
	for(j=0;j<n;j++)
	{
		printf("Room-%d:",j+1);
		scanf("\n%c",&se);
		for(l=1;l<strlen(a);l++)
		{
			if(a[l]==se) break;
		}
		if(l<strlen(a))
		{
			li[i]=se;
			i++;
		}
		else 
		{
			printf("kindly select available rooms\n");
			j--;
		}
	}
	printf("\nEnter details of passengers\n\n");
	for(i=0;i<n;i++)
	{
		printf("\nPassenger-%d Details:",i+1);
		printf("\nEnter name:");
		scanf(" %[^\n]",det.name);
                //getchar();
		printf("Enter gender(M/F/T):");
		scanf(" %c",&det.gender);
		printf("Enter age:");
		scanf("%d",&det.age);
		printf("Enter proof of identity:");
		scanf("%s",det.proof);
		printf("Enter class(First/Second/Third):");
		scanf("%s",det.Class);
		printf("Enter the boarding Port:");
		scanf("%s",det.src);
		printf("Enter the destination:");
		scanf("%s",det.dest);
		addend(L,det);
	}
	p=insert1();
	p=book_1(p,li,det.name,i);
	update(p,"today.txt");
	if(det.Class[0]=='f'||det.Class[0]=='F')payment(1,n);
	else if(det.Class[0]=='s'||det.Class[0]=='S')payment(2,n);
	else payment(3,n);	
	return;			
}

int main()
{
	details d[100];
	route r[100];
	List L=CreateEmptyList();
	int ch;
	int Graph[5][5];
	stationInitialise(Graph);
	while(1)
	{
		printf("\n\t\t\tMenu");
		printf("\n\t\t1.Book\n\t\t2.Booking Status\n\t\t3.Cancel Booking/Check-Out\n\t\t4.Routes available\n\t\t5.Room Availability");
		printf("\n\t\t0.Exit\n\t\tEnter Choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1 :Book(L);break;
			case 2 : Status(L);
					break;
			case 3 : Cancel1(L);
				 printf("Refund process is initiated\n");
				 printf("You will receive your refund within 7-working days\n");
					break;
			case 4 :Routes(Graph);
					break;
			case 5 : Chart();
					break;
			case 0 : exit(0);
			default : printf("Invalid Choice ");
		}
	}
    return 0;
}
