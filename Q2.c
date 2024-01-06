#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 4
void calculateNeedMatrix(int need[MAX_PROCESSES][MAX_RESOURCES], int
max[MAX_PROCESSES][MAX_RESOURCES], int
allocation[MAX_PROCESSES][MAX_RESOURCES]);
bool checkSafety(int available[MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
int allocation[MAX_PROCESSES][MAX_RESOURCES], int
need[MAX_PROCESSES][MAX_RESOURCES], int safeSeq[MAX_PROCESSES]);
void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rowCount, int colCount, const
char *title);
int main() {
 int max[MAX_PROCESSES][MAX_RESOURCES] = {
 {0, 0, 1, 2},
 {2, 7, 5, 0},
 {6, 6, 5, 6},
 {4, 3, 5, 6},
 {0, 6, 5, 2}
 };
 int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
 {0, 0, 1, 2},
 {2, 0, 0, 0},
 {0, 0, 3, 4},
 {2, 3, 5, 4},
 {0, 3, 3, 2}
 };

 int available[MAX_RESOURCES] = {6, 7, 12, 12};
 int need[MAX_PROCESSES][MAX_RESOURCES];

 calculateNeedMatrix(need, max, allocation);

 printMatrix(need, MAX_PROCESSES, MAX_RESOURCES, "Need Matrix");

 int safeSeq[MAX_PROCESSES];
 bool isSafe = checkSafety(available, max, allocation, need, safeSeq);
 if (isSafe) {
 printf("\nThe system is in a safe state.\nSafe Sequence: ");
 for (int i = 0; i < MAX_PROCESSES; i++) {
 printf("P%d ", safeSeq[i]);
 }
 printf("\n");

 int requestProcess = 2; // P3
 int requestResource = 1; // R2
 int requestInstances = 1;

 if (requestInstances <= need[requestProcess][requestResource] &&
 requestInstances <= available[requestResource]) {

 available[requestResource] -= requestInstances;
 allocation[requestProcess][requestResource] += requestInstances;
 need[requestProcess][requestResource] -= requestInstances;
 printf("\nThe request can be granted immediately.\n");
 } else {
 printf("\nThe request cannot be granted immediately.\n");
 }
 } else {
 printf("\nThe system is not in a safe state.\n");
 }
 return 0;
}
void calculateNeedMatrix(int need[MAX_PROCESSES][MAX_RESOURCES], int
max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES])
{
 for (int i = 0; i < MAX_PROCESSES; i++) {
 for (int j = 0; j < MAX_RESOURCES; j++) {
 need[i][j] = max[i][j] - allocation[i][j];
 }
 }
}
bool checkSafety(int available[MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
int allocation[MAX_PROCESSES][MAX_RESOURCES], int
need[MAX_PROCESSES][MAX_RESOURCES], int safeSeq[MAX_PROCESSES]) {
 bool finish[MAX_PROCESSES] = {false};
 int work[MAX_RESOURCES];
 for (int i = 0; i < MAX_RESOURCES; i++) {
 work[i] = available[i];
 }
 int count = 0;
 while (count < MAX_PROCESSES) {
 bool found = false;
 for (int i = 0; i < MAX_PROCESSES; i++) {
 if (!finish[i]) {
 int j;
 for (j = 0; j < MAX_RESOURCES; j++) {
 if (need[i][j] > work[j]) {
 break;
 }
 }
 if (j == MAX_RESOURCES) {
 for (int k = 0; k < MAX_RESOURCES; k++) {
 work[k] += allocation[i][k];
 }
 safeSeq[count++] = i;
 finish[i] = true;
 found = true;
 }
 }
 }
 if (!found) {
 break;
 }
 }
 return count == MAX_PROCESSES;
}
void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rowCount, int colCount, const
char *title) {
 printf("\n%s:\n", title);
 for (int i = 0; i < rowCount; i++) {
 for (int j = 0; j < colCount; j++) {
 printf("%d ", matrix[i][j]);
 }
 printf("\n");
 }
}
