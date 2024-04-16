#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {4, 0, 0},
    {5, 0, 4},
    {4, 3, 3},
    {2, 2, 4}
};

int request[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 0, 0},
    {5, 2, 2},
    {1, 0, 4},
    {4, 4, 4},
    {6, 5, 5}
};

int available[MAX_RESOURCES] = {7, 2, 6};

int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = request[i][j] - allocation[i][j];
        }
    }
}

void acceptAvailable() {
    printf("Enter Available Resources (A B C): ");
    scanf("%d %d %d", &available[0], &available[1], &available[2]);
}

void displayAllocationMax() {
    printf("\nProcess\tAllocation\tRequest\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        printf("P%d\t", i);
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", request[i][j]);
        }
        printf("\n");
    }
}

void displayNeed() {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailable() {
    printf("\nAvailable Resources: %d %d %d\n", available[0], available[1], available[2]);
}

int main() {
    char choice;

    calculateNeed();

    do {
        printf("\nMenu:\n");
        printf("a) Accept Available\n");
        printf("b) Display Allocation, Request\n");
        printf("c) Display Need\n");
        printf("d) Display Available\n");
        printf("e) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                acceptAvailable();
                break;
            case 'b':
                displayAllocationMax();
                break;
            case 'c':
                displayNeed();
                break;
            case 'd':
                displayAvailable();
                break;
            case 'e':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 'e');

    return 0;
}
