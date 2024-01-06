#include <stdio.h>
#include <stdbool.h>
typedef struct {
 int pid;
 int arrivalTime;
 int burstTime;
 int remainingTime;
 int startTime;
 int endTime;
 int waitingTime;
 int turnaroundTime;
 int responseTime;
} Process;
void sortProcessesByArrival(Process proc[], int n) {
 Process temp;
 for (int i = 0; i < n - 1; i++) {
 for (int j = i + 1; j < n; j++) {
 if (proc[i].arrivalTime > proc[j].arrivalTime) {
 temp = proc[i];
 proc[i] = proc[j];
 proc[j] = temp;
 }
 }
 }
}
void printGanttChart(Process proc[], int n, const char* title) {
 printf("\n%s Gantt Chart:\n", title);
 for (int i = 0; i < n; i++) {
 printf("|");
 for (int j = 0; j < proc[i].burstTime; j++) {
 printf("-");
 }
 printf("P%d", proc[i].pid);
 for (int j = 0; j < proc[i].burstTime; j++) {
 printf("-");
 }
 }
 printf("|\n0");
 for (int i = 0, totalTime = 0; i < n; i++) {
 totalTime += proc[i].burstTime;
 for (int j = 0; j < 2 * proc[i].burstTime + 2; j++) {
 printf(" ");
 }
 printf("%d", totalTime);
 }
 printf("\n");
}
float calculateAverageTime(Process proc[], int n, const char* type) {
 int totalTime = 0;
 float totalWaitingTime = 0;
 for (int i = 0; i < n; i++) {
 proc[i].startTime = totalTime;
 proc[i].waitingTime = totalTime - proc[i].arrivalTime;
 totalTime += proc[i].burstTime;
 proc[i].endTime = totalTime;
 proc[i].turnaroundTime = totalTime - proc[i].arrivalTime;
 totalWaitingTime += proc[i].waitingTime;
 }
 float averageTime = totalWaitingTime / n;
 printf("%s Average Waiting Time = %.2f\n", type, averageTime);
 return averageTime;
}
void FCFFS(Process proc[], int n) {
 sortProcessesByArrival(proc, n);
 float FCFSavgTime = calculateAverageTime(proc, n, "FCFS");
 printGanttChart(proc, n, "FCFS");
}
float RoundRobin(Process proc[], int n, int quantum) {
 int time = 0, remainingProcesses = n, i = 0, procCount = 0;
 Process executedOrder[100]; // Assuming a max of 100 executions for simplicity
 bool done;
 while (remainingProcesses != 0) {
 done = true;
 if (proc[i].remainingTime > 0) {
 done = false;
 if (proc[i].remainingTime > quantum) {
 time += quantum;
 proc[i].remainingTime -= quantum;
 } else {
 time += proc[i].remainingTime;
 proc[i].waitingTime = time - proc[i].burstTime;
 proc[i].remainingTime = 0;
 remainingProcesses--;
 }
 executedOrder[procCount++] = proc[i];
 }
 i = (i + 1) % n;
 if (done) break;
 }
 float RRavgTime = calculateAverageTime(executedOrder, procCount, "RR");
 printGanttChart(executedOrder, procCount, "RR");
 return RRavgTime;
}
int main() {
 int n, quantum;
 printf("Enter the number of processes: ");
 scanf("%d", &n);
 Process proc[n], procCopy[n];
 for (int i = 0; i < n; i++) {
 printf("Enter arrival time and burst time for process %d: ", i + 1);
 scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
 proc[i].pid = i + 1;
 proc[i].remainingTime = proc[i].burstTime;
 procCopy[i] = proc[i];
 }
 printf("Enter time quantum for Round Robin: ");
 scanf("%d", &quantum);
 printf("\nRunning FCFS Scheduling...\n");
 FCFFS(proc, n);
 printf("\nRunning Round Robin Scheduling...\n");
 float FCFSavgTime = calculateAverageTime(proc, n, "FCFS");
 float RRavgTime = RoundRobin(procCopy, n, quantum);
 if (RRavgTime < FCFSavgTime) {
 printf("\nRound Robin results in the minimum average waiting time.\n");
 } else {
 printf("\nFCFS results in the minimum average waiting time.\n");
 }
 return 0;
}