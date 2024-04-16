#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int n, m;

void acceptInput() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; ++i) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &need[i][j]);
        }
    }
}

bool isSafeState(int process, int request[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };

    for (int i = 0; i < m; ++i) {
        work[i] = available[i];
    }

    for (int i = 0; i < m; ++i) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds maximum claim.\n");
            return false;
        }
    }

    for (int i = 0; i < m; ++i) {
        if (request[i] > work[i]) {
            printf("Error: Insufficient resources available.\n");
            return false;
        }
    }

    for (int i = 0; i < m; ++i) {
        work[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            for (int i = 0; i < m; ++i) {
                work[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
            printf("System is not in a safe state.\n");
            return false;
        }
    }
    printf("System is in a safe state.\n");
    return true;
}

int main() {
    acceptInput();

    int process;
    printf("Enter the process number to make a request: ");
    scanf("%d", &process);

    int request[MAX_RESOURCES];
    printf("Enter the request for process P%d: ", process);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &request[i]);
    }

    isSafeState(process, request);

    return 0;
}
