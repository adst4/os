#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_BLOCKS 100

typedef struct Block {
    int blockNumber;
    struct Block* next;
} Block;

Block* disk[MAX_BLOCKS];
bool allocated[MAX_BLOCKS];

int n;

void initializeDisk() {
    for (int i = 0; i < n; ++i) {
        disk[i] = NULL;
        allocated[i] = false;
    }
}

void showBitVector() {
    printf("Bit Vector:\n");
    for (int i = 0; i < n; ++i) {
        if (allocated[i]) {
            printf("1 ");
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

int getFreeBlock() {
    for (int i = 0; i < n; ++i) {
        if (!allocated[i]) {
            return i;
        }
    }
    return -1; // No free block available
}

void createNewFile() {
    int fileSize;
    printf("Enter the file size: ");
    scanf("%d", &fileSize);

    int blocksNeeded = (fileSize + sizeof(Block) - 1) / sizeof(Block);

    printf("File needs %d blocks.\n", blocksNeeded);

    int startBlock = getFreeBlock();
    if (startBlock == -1) {
        printf("Error: No free blocks available for file allocation.\n");
        return;
    }

    int currentBlock = startBlock;
    for (int i = 1; i < blocksNeeded; ++i) {
        int nextBlock = getFreeBlock();
        if (nextBlock == -1) {
            printf("Error: Not enough contiguous free blocks for file allocation.\n");
            return;
        }
        disk[currentBlock] = (Block*)malloc(sizeof(Block));
        disk[currentBlock]->blockNumber = nextBlock;
        allocated[nextBlock] = true;
        currentBlock = nextBlock;
    }

    printf("File created successfully. Start block: %d\n", startBlock);
}

void showDirectory() {
    printf("Directory:\n");
    for (int i = 0; i < n; ++i) {
        if (allocated[i]) {
            printf("Block %d -> ", i);
            Block* currentBlock = disk[i];
            while (currentBlock != NULL) {
                printf("%d -> ", currentBlock->blockNumber);
                currentBlock = currentBlock->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    srand(time(NULL));

    printf("Enter the number of blocks on the disk: ");
    scanf("%d", &n);

    initializeDisk();

    char choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                showBitVector();
                break;
            case '2':
                createNewFile();
                break;
            case '3':
                showDirectory();
                break;
            case '4':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != '4');

    // Free allocated memory
    for (int i = 0; i < n; ++i) {
        Block* currentBlock = disk[i];
        while (currentBlock != NULL) {
            Block* temp = currentBlock;
            currentBlock = currentBlock->next;
            free(temp);
        }
    }

    return 0;
}
