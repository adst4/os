#include<stdio.h>
#include<stdlib.h>
#define MAX 100

void showBitVector(int n);
void createFile(int n);
void showFiles(int n);

typedef struct file
{
    char fname[50];
    int blocks[10]; // Changed to an array to store block indices
    int length;
} File;

File file[10];
int f[MAX];
int number=0;

int main()
{

    int choice,n,i;

    printf("Enter How Many Blocks : ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        f[i]=rand()%2;
    }

    do
    {
        printf("\n1 : Show Bit Vector\n");
        printf("2 : Create New File\n");
        printf("3 : Show All Files\n");
        printf("4 : Exit\n");
        printf("Enter Your choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1 : 
                showBitVector(n);
                break;

            case 2:
				createFile(n);
                break;

            case 3:
				showFiles(n);
                break;

            case 4:
                    exit(0);
                break;

            default : printf("Invalid Choice.....");
        }
       
    }while (choice!=4);
    return 0;
}

void showBitVector(int n)
{
    int i;
    printf("Bit Vector : ");
    for(i=0;i<n;i++)
    {
        printf("%d\t",f[i]);
    }
}

void createFile(int n)
{
    int i, cnt = 0;
	
    printf("Enter File Name : ");
    scanf("%s", file[number].fname);
    printf("Enter File Length : ");
    scanf("%d", &file[number].length);
	
    if(n >= file[number].length)
    {
        for(i = 0; i < n; i++)
        {
            if(f[i] == 0)
            {
                cnt++;
                if(cnt == file[number].length)
                {
                    for(int j = 0; j < file[number].length; j++)
                    {
                        file[number].blocks[j] = i - cnt + 1 + j;
                        f[i - cnt + 1 + j] = 1;
                    }
                    printf("File Successfully Created...\n");
                    number++;
                    return;
                }
            }
            else
            {
                cnt = 0; // Reset the counter if a block is not free
            }
        }
        printf("Not enough contiguous blocks available to create the file\n");
    }
    else
    {
        printf("Not enough total blocks available to create the file\n");
    }
}


void showFiles(int n)
{
	int i, j;
	printf("Name\tBlocks\tLength\n");
	for(i=0;i<number;i++)
	{
	    printf("%s\t",file[i].fname);
	    for(j=0;j<file[i].length;j++)
	    {
	        printf("%d ", file[i].blocks[j]);
	    }
	    printf("\t%d\n", file[i].length);
	}
}