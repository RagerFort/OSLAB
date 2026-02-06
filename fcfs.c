#include <stdio.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
} Process;

void sortByArrival(Process proc[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrivalTime > proc[j + 1].arrivalTime) {
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    // ==========================================
    // E A S Y   T O   C H A N G E   I N P U T S
    // ==========================================
    Process proc[] = {
        {1, 0, 10}, // {PID, Arrival, Burst}
        {2, 1, 5},
        {3, 3, 2},
        {4, 5, 20}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    // ==========================================

    // Step 1: Sort by Arrival Time
    sortByArrival(proc, n);

    int currentTime = 0;

    // Step 2: Process Loop
    for (int i = 0; i < n; i++) {
        // Handle idle CPU time
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime;
        }

        // Execute
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnAroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnAroundTime - proc[i].burstTime;

        // Advance time
        currentTime = proc[i].completionTime;
    }

    // Output
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", 
               proc[i].pid, 
               proc[i].arrivalTime, 
               proc[i].burstTime, 
               proc[i].waitingTime, 
               proc[i].turnAroundTime);
    }

    return 0;
}