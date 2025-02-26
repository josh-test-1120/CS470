#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Execution order variables
    char *execOrder[1000];
    char buffer[14];
    int execLength = 0;
    
    int totalTime = 0;

    // Keep traversing processes in round-robin manner until all of them are not done
    while (1) {
        int done = 1;
        int waitTime;

        // Iterate through the processes and account for quantum ticks
        for (int i = 0; i < n; i++) {
            waitTime = 0;
            // If remaining time of a process is greater than 0
            // then only need to process further
            if (proc[i].remaining_time > 0) {
                // Update done variable since some process is not done
                done = 0;
                // Update the execution order array pointer
                snprintf(buffer, sizeof(buffer), "P%d ", proc[i].process_id);
                execOrder[execLength] = strdup(buffer);
                execLength++;

                // Calculate wait time
                if (proc[i].remaining_time < quantum) waitTime = proc[i].remaining_time;
                else waitTime = quantum;
                totalTime += waitTime;

                // Update remaining time
                proc[i].remaining_time = proc[i].remaining_time - waitTime;
            }
            // Walk through and update the wait times
            for (int j = 0; j < n; j++) {
                if ((i != j) && (proc[j].remaining_time > 0)) {
                    // Update the waiting time
                    proc[j].waiting_time += waitTime;
                }
            }
        }
        // If all processes are done
        if (done == 1) break;
    }

    // Print the execution order
    printf("Execution Order: ");
    for (int x = 0; x < execLength; x++) {
        printf("%s", execOrder[x]);
    }
    printf("\n");
    
}

// Function to calculate waiting times and execution order for all processes
void initializeRemainingTime(Process proc[], int n) {
    // Loop through the processes and initialize the remaining time
    for (int i = 0; i < n; i++) proc[i].remaining_time = proc[i].burst_time;
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
   for (int i = 0; i < n; i++) proc[i].turnaround_time =
        proc[i].burst_time + proc[i].waiting_time;
}

// Calculate average wait times and turnaround times
void calculateAverageTimes(Process proc[], int n) {
    // Variables
    double waitSum = 0.0;
    double turnaroundSum = 0.0;


    // Iterate through the processes and do the summations
    for (int i = 0; i < n; i++) {
        waitSum += proc[i].waiting_time;
        turnaroundSum += proc[i].turnaround_time;
    }
    // Calculate the averages
    waitSum = waitSum / n;
    turnaroundSum = turnaroundSum / n;

    // Output the information
    printf("The average wait time for this algorithm is: %.2f\n", waitSum);
    printf("The average turnaround time for this algorithm is: %.2f\n", turnaroundSum);
}

// This is the function that runs the round robin processes
void roundRobin(Process proc[], int n, int quantum) {
    initializeRemainingTime(proc, n);
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

// This is the function to output the process details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

// This is the main process
int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    //Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}, {4, 0, 7}, {5, 0, 15}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 
    roundRobin(proc, n, quantum);
    printProcesses(proc, n);
    calculateAverageTimes(proc, n);

    return 0;
}
