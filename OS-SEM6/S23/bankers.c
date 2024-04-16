#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

// Function prototypes
void displayNeedMatrix();
int checkSafeState(int process, int request[]);

int main() {
    int i, j;
    
    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);
    
    // Input available resources
    printf("Enter available resources:\n");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }
    
    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    // Input maximum requirement matrix
    printf("Enter maximum requirement matrix:\n");
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
            // Calculate need matrix
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    
    // Display the need matrix
    printf("Need matrix:\n");
    displayNeedMatrix();
    
    // Check if a given request of a process can be granted immediately
    int process;
    printf("Enter process number (0-indexed): ");
    scanf("%d", &process);
    int request[MAX_RESOURCES];
    printf("Enter the request for process %d:\n", process);
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &request[i]);
    }
    if (checkSafeState(process, request)) {
        printf("Request can be granted immediately.\n");
    } else {
        printf("Request cannot be granted immediately.\n");
    }

    return 0;
}

// Function to display the contents of the need matrix
void displayNeedMatrix() {
    int i, j;
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the system is in a safe state after granting a request
int checkSafeState(int process, int request[]) {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0}; // Initialize all processes as not finished

    // Initialize work to available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Allocate resources to the process temporarily
    for (int i = 0; i < num_resources; i++) {
        if (request[i] <= work[i]) {
            work[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        } else {
            // Insufficient resources available
            return 0;
        }
    }

    // Check if the system is in a safe state after allocation
    int count = 0;
    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == num_resources) {
                    // Process can be finished and resources released
                    finish[i] = 1;
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) {
            // No process found that can finish
            break;
        }
    }

    // Check if all processes are finished
    if (count == num_processes) {
        return 1; // System is in a safe state
    } else {
        // Roll back the allocation
        for (int i = 0; i < num_resources; i++) {
            work[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return 0; // System is not in a
