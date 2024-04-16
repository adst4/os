#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void showBitVector(int n);
void createFile(int n);
void showFiles(int n);

typedef struct file {
    char fname[50];
    int length;
    int block[MAX];
    struct file *next;
} File;

File file[10];
int f[MAX];
int number = 0;

int main() {

    int choice, n, i;

    printf("Enter How Many Blocks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        f[i] = rand() % 2;
    }

    do {
        printf("\n\n1: Show Bit Vector\n");
        printf("2: Create New File\n");
        printf("3: Show All Directory\n");
        printf("4: Exit\n");
        printf("Enter Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
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

            default:
                printf("Invalid Choice.....");
        }

    } while (choice != 4);
    return 0;
}

void showBitVector(int n) {
    int i;
    printf("Bit Vector: ");
    for (i = 0; i < n; i++) {
        printf("%d\t", f[i]);
    }
}

void createFile(int n) {
    int i, cnt = 0;

    printf("Enter File Name: ");
    scanf("%s", file[number].fname);

    printf("Enter File Length: ");
    scanf("%d", &file[number].length);

    if (n >= file[number].length) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                cnt++;
                if (cnt == file[number].length) {
                    int j = i;
                    while (cnt > 0) {
                        if (f[j] == 0) {
                            f[j] = 1;
                            cnt--;
                            file[number].block[cnt] = j;
                        }
                        j--;
                    }
                    printf("File Created Successfully...");
                    number++;
                    return;
                }
            }
        }
        printf("File Not Created..");
    }
}

void showFiles(int n) {
    int i, j;
    printf("Name\tLength\tLinked Blocks\n");
    for (i = 0; i < number; i++) {
        printf("%s\t%d\t", file[i].fname, file[i].length);
        for (j = 0; j < file[i].length; j++) {
            printf("-->%d", file[i].block[j]);
        }
        printf("\n");
    }
}
