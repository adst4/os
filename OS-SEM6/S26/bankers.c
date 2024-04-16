#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 0, 1, 2},
    {1, 0, 0, 0},
    {1, 3, 5, 4},
    {0, 6, 3, 2},
    {0, 0, 1, 4}
};

int max[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 0, 1, 2},
    {1, 7, 5, 0},
    {2, 3, 5, 6},
    {0, 6, 5, 2},
    {0, 6, 5, 6}
};

int available[MAX_RESOURCES] = {1, 5, 2, 0};

int need[MAX_PROCESSES][MAX_RESOURCES];

bool finish[MAX_PROCESSES];

void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] = available[i];
    }

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        finish[i] = false;
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < MAX_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found) {
            // No process found that can run
            return false;
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    calculateNeed();
    printf("Need Matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    if (isSafe()) {
        printf("System is in safe state.\n");
    } else {
        printf("System is not in safe state.\n");
    }

    return 0;
}
