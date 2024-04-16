#include<stdio.h>
#include<stdlib.h>
#define MAX 20

int main()
{
	int a[MAX];
	int head;
	int prev,i,n;
	int sum=0;
	
	printf("How Many Disk Blocks : ");
	scanf("%d",&n);
	
	printf("Enter Request String : ");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
		
	printf("Enter Start Head Possition : ");
	scanf("%d",&head);
	
	prev=head;
	for(i=0;i<n;i++)
	{
		if(prev<a[i])
		{
			sum+=a[i]-prev;
		}
		else
		{
			sum+=prev-a[i];
		}
		prev=a[i];
	}
	
	printf("Head Positions : --->%d",head);
	for(i=0;i<n;i++)
	{
		printf("--->%d",a[i]);
	}
	
	printf("\nTotal Number Of Seek Operation : %d",sum);
	
}