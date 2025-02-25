#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;


int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        // Let's get the next process based on lowest remaining time,
        // the process is not complete, and arrival time is not in the future
        if ((proc[i].remaining_time < min_time) && (proc[i].is_completed == 0)
            && (proc[i].arrival_time <= current_time)) {
                min_time = proc[i].remaining_time; // update minimum time
                index = i; // update index
        }
    }
    // Return the index of the next process
    return index;
}

// Process handling function to process the cpu time tick
void processHandle(Process proc[], int index, int current_time, int prev) {
    // Handle output of Time stamp when context switching
    if (prev != index)
        printf("Time %d: Process %d starts...\n", current_time, proc[index].process_id);

    // Update remaining time
    proc[index].remaining_time--;
    // Update Turnaround time
    if (proc[index].remaining_time == 0) {
        // Calculate the turnaround time
        proc[index].turnaround_time = proc[index].burst_time + proc[index].waiting_time;
        proc[index].is_completed = 1;
        printf("Time %d: Process %d completed.\n", current_time + 1, proc[index].process_id);
    }
    // Walk through and update the wait times
    for (int j = 0; j < n; j++) {
        if ((index != j) && (proc[j].remaining_time > 0)
            && (proc[j].arrival_time <= current_time)) {
                // Update the waiting time
                proc[j].waiting_time++;
        }
    }
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    // Variables for handling details about preemption
    int current_time = 0;
    int completed = 0;
    int prev = -1;

    // Initialize waiting times, remaining times, and is_completed
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].is_completed = 0;
    }
    
    // Build the loop to execute processes in the queue list
    while (completed != n) {
        // Get the index of the next process based on burst time
        int index = findNextProcess(proc, current_time);
        // If the current time has a process to run
        if (current_time <= n)
            // Check if arrived packet should run instead of next index
            // and handle process with lowest remaining time
            if (proc[index].remaining_time < proc[current_time].remaining_time)
                processHandle(proc, index, current_time, prev);
            else processHandle(proc, current_time, current_time, prev);
        // For cases where current time is larger than process array
        else processHandle(proc, index, current_time, prev);

        // Updated completed counter
        if (proc[index].is_completed == 1) completed++;
        prev = index; // Assign previous index
        current_time++; // Update the clock tick
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    //Process proc[] = {{1, 0, 8}, {2, 1, 5}, {3, 2, 9}, {4, 3, 5}, {5, 4, 2}, {6, 4, 6}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}
