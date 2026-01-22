#include <stdio.h>
#include <stdbool.h>

// Define a maximum number of processes for static array sizing
#define MAX_PROCESSES 100

// 1. Structure to keep Process data organized
// If you need to add "Priority", just add 'int priority;' here.
typedef struct {
    int id;             // Process ID (e.g., 1, 2, 3)
    int burstTime;      // Total time required by the process
    int remainingTime;  // Time left to complete
    int arrivalTime;    // When the process arrived
    int waitingTime;    // How long it waited
    int turnAroundTime; // Total time from arrival to completion
    int completionTime; // When it actually finished
} Process;

int main() {
    Process p[MAX_PROCESSES];
    int n, quantum;
    int currentTime = 0;
    int completedCount = 0;

    // --- INPUT SECTION ---
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Input details for each process
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d Arrival Time: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &p[i].burstTime);
        
        // Initially, remaining time is same as burst time
        p[i].remainingTime = p[i].burstTime; 
    }

    // --- SCHEDULING LOGIC ---
    printf("\n--- Starting Round Robin Scheduling ---\n");
    
    // We keep looping until all processes are completed
    while (completedCount < n) {
        bool idle = true; // Flag to check if CPU was idle this cycle

        for (int i = 0; i < n; i++) {
            // Check if process has arrived AND has time remaining
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                
                idle = false; // CPU is doing work

                if (p[i].remainingTime > quantum) {
                    // Process needs more time than the quantum
                    currentTime += quantum;
                    p[i].remainingTime -= quantum;
                } else {
                    // Process will finish in this turn
                    currentTime += p[i].remainingTime;
                    p[i].remainingTime = 0;
                    
                    // CALCULATION: Process is done
                    completedCount++;
                    p[i].completionTime = currentTime;
                    p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
                }
            }
        }

        // If no process has arrived yet, advance time to avoid infinite loop
        if (idle) {
            currentTime++;
        }
    }

    // --- OUTPUT SECTION ---
    printf("\n-----------------------------------------------------------------------\n");
    printf("ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("-----------------------------------------------------------------------\n");

    float avgWait = 0, avgTurn = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
               p[i].id, 
               p[i].arrivalTime, 
               p[i].burstTime, 
               p[i].completionTime, 
               p[i].turnAroundTime, 
               p[i].waitingTime);
               
        avgWait += p[i].waitingTime;
        avgTurn += p[i].turnAroundTime;
    }

    printf("-----------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", avgWait / n);
    printf("Average Turnaround Time: %.2f\n", avgTurn / n);

    return 0;
}