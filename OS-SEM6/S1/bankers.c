#include<stdio.h>
#include<stdlib.h>
#define MAX 50

int allocation[MAX][MAX];
int maximum[MAX][MAX];
int need[MAX][MAX];
int available[MAX];

int p,r;

void accept()
{
	int i,j;
	printf("Enter Availale Resource : ");
	for(i=0;i<r;i++)
		scanf("%d",&available[i]);
		
	printf("\nEnter Allocation Matrix : \n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&allocation[i][j]);
		}	
	}
	
	printf("\nEnter Maximum Matrix : \n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			scanf("%d",&maximum[i][j]);
		}	
	}
}

void display()
{
	int i,j;
	printf("\nAllocation Matrix : \n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%d\t",allocation[i][j]);
		}
		printf("\n");	
	}
	
	printf("\nMaximum Matrix : \n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%d\t",maximum[i][j]);
		}
		printf("\n");	
	}
}

void calculateNeed()
{
	int i,j;
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			need[i][j]=maximum[i][j]-allocation[i][j];
		}	
	}
	
	printf("\nNeed Matrix : \n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%d\t",need[i][j]);
		}
		printf("\n");	
	}
}

int main()
{
	int choice,i;
	
	do
	{
		printf("\n1 : Accept Available\n");
		printf("2 : Display Allocation, Max\n");
		printf("3 : Display the contents of need matrix\n");
		printf("4 : Display Available\n");
		printf("5 : Exit\n");
		printf("Enter Your Choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("How Many Process : ");
				scanf("%d",&p);
				printf("How Many Resourse : ");
				scanf("%d",&r);
				accept();
				break;
				
			case 2:
				display();
				break;
				
			case 3:
				calculateNeed();
				break;
				
			case 4:
				
				printf("\nAvailable : ");
				for(i=0;i<r;i++)
				{
					printf("%d\t",available[i]);
				}
				break;
				
			case 5:
				exit(0);
				break;
				
			default : printf("Invalid choice .....!");
		}
	}while(choice!=5);
	return 0;
}