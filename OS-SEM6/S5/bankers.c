#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int m, n;

void acceptInput() {
    printf("Enter the number of resource types (n): ");
    scanf("%d", &n);

    printf("Enter the number of processes (m): ");
    scanf("%d", &m);

    printf("Enter the number of instances for each resource type:\n");
    for (int i = 0; i < n; ++i) {
        printf("Resource type %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < m; ++i) {
        printf("For process P%d: ", i);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < m; ++i) {
        printf("For process P%d: ", i);
        for (int j = 0; j < n; ++j) {
            scanf("%d", &maximum[i][j]);
        }
    }
}

void calculateNeed() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool checkRequest(int process, int request[]) {
    for (int i = 0; i < n; ++i) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    acceptInput();
    calculateNeed();

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < m; ++i) {
        printf("P%d: ", i);
        for (int j = 0; j < n; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int process;
    printf("\nEnter the process number to check request: ");
    scanf("%d", &process);

    int request[MAX_RESOURCES];
    printf("Enter the request for process P%d: ", process);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &request[i]);
    }

    if (checkRequest(process, request)) {
        printf("The request can be granted immediately.\n");
    } else {
        printf("The request cannot be granted immediately.\n");
    }

    return 0;
}
