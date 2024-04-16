#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20

int main() {
    int array[MAX];
    int i, j, n;
    int head;
    int sum = 0;

    printf("Enter the number of disk blocks: ");
    scanf("%d", &n);

    printf("Enter the request string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    printf("Enter the head position: ");
    scanf("%d", &head);

    int visited[MAX] = {0};
    int min_distance, min_index;

    int sequence[MAX] = {0};
    int sequence_index = 0;

    for (i = 0; i < n; i++) {
        min_distance = INT_MAX;
        for (j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(head - array[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        visited[min_index] = 1;
        head = array[min_index];
        sum += min_distance;
        sequence[sequence_index++] = head;
    }

    printf("Total seek time using SSTF: %d\n", sum);
    printf("Sequence of head movements: ");
    for (i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}