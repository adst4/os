#include<stdio.h>
#include<stdlib.h>
#define MAX 20

int request[MAX];
int n, head, size;

int search()
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(head < request[i])
            return i;
    }
    return -1;
}

int sort()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(request[j] > request[j + 1])
            {
                int temp = request[j];   
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }
}

int scan()
{
    int sum = 0;
    int i, j = 0;
    int index, sequence[MAX];
    
    sort();
    
    index = search();
    
    for(i = index; i < n; i++)
    {
        sum += abs(request[i] - head);
        sequence[j++] = request[i];
        head = request[i];
    }
    
    for(i = 0; i < index; i++)
    {
        sum += abs(request[i] - head);
        sequence[j++] = request[i];
        head = request[i];
    }


    
    printf("Seek Sequence: ");
    for(i = 0; i < n; i++)
    {
        printf("%d\t", sequence[i]);
    }
    return sum;
}

int main()
{
    int i;
    printf("Enter How Many Blocks: ");
    scanf("%d", &n);
    
    printf("Enter Requests: \n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }
    
    printf("Enter Head: ");
    scanf("%d", &head);
  
    printf("Total Seek Time: %d", scan());
    return 0;
}
