#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char dest[100];
    int vertex;
    int dist;
    struct node* link;
};
struct node* graph[20];
char p[][20] = {"Chennai","Mumbai","Andhaman","Lakshwadeep","Sri Lanka"};

void init(int n)
{
    for(int i=0;i<n;i++)
    {
        graph[i]=malloc(sizeof(struct node));
        graph[i]->vertex=-1;
        graph[i]->dist=0;
        strcpy(graph[i]->dest,p[i]);
        graph[i]->link=NULL;
    }    
    return ;
}


void addEdge(int src, int dest, char ar[],int dist)
{
    struct node* New = malloc(sizeof(struct node));
    New->vertex=dest;
    New->link=NULL;
    strcpy(New->dest,ar);
    New->dist=dist;

    struct node* temp=graph[src];
    
    while(temp->link!=NULL)
    {
        temp=temp->link;

    }

    temp->link=New;

}

void printGraph(int n)
{
    int v;
    for (v = 0; v < n; ++v)
    {
        printf("%s -> ",graph[v]->dest);
        struct node* temp = graph[v]->link;
        while (temp!=NULL)
        {
            printf("%s(%d) ", temp->dest,temp->dist);
            temp = temp->link;
        }
        printf("\n");
    }
}

void ListtoMatrix(int G[][5])
{
    for (int v = 0; v < 5; ++v)
    {
        struct node* temp = graph[v]->link;
        while (temp!=NULL)
        {
        	G[v][temp->vertex]=temp->dist;
            temp = temp->link;
        }
    }
}

void stationInitialise(int G[][5])
{
    init(5);
    /*
    0-Chennai
    1-Villupuram
    2-Pondicherry
    3-Madurai
    4-Coimbatore
    */

    addEdge(0,4,p[4],1680);
    addEdge(4,0,p[0],1680);
    addEdge(0,1,p[1],5130);
    addEdge(1,0,p[0],5130);
    addEdge(0,3,p[3],1650);
    addEdge(3,0,p[0],1650);
    
    addEdge(4,1,p[1],3370);
    addEdge(1,4,p[4],3370);
	addEdge(4,2,p[2],2940);
	addEdge(2,4,p[4],2940);
    addEdge(4,3,p[3],910);
    addEdge(3,4,p[4],910);
    
    addEdge(3,2,p[2],3000);
    addEdge(2,3,p[3],3000);
    
    addEdge(2,1,p[1],2360);
	addEdge(1,2,p[2],2360);
	
	//printGraph(5);
	
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			G[i][j]=0;
	/*
	printf("\nBefore List to Matrix \n");
	
	for(int i=0;i<5;i++)
	{
		printf("%d-> %s\t",i,p[i]);
		for(int j=0;j<5;j++)
		{
			printf("%d ",G[i][j]);
		}
		printf("\n");
	}
	*/
	
	ListtoMatrix(G);
	
	/*
	printf("\nAfter List to Matrix \n");
    printf("\t\tChennai\tCBE\tMadurai\tPondi\tVillupuram\n");
	for(int i=0;i<5;i++)
	{
		printf("%s\t",p[i]);
		for(int j=0;j<5;j++)
		{
			printf("%d\t",G[i][j]);
		}
		printf("\n");
	}
	*/
}
