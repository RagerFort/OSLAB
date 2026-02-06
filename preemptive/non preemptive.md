Here are the implementations for Non-Preemptive Priority Scheduling.

How it works:

The CPU is assigned to the process with the highest priority (in these examples, a lower number indicates higher priority).

Non-Preemptive: Once a process starts, it runs completely until it finishes. The CPU cannot be taken away midway, even if a more important process arrives during execution.

1. C++ Implementation
This version jumps the currentTime forward by the burst length since it doesn't need to check every second.

C++

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority; // Lower number = Higher priority
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
};

int main() {
    // ==========================================
    // E A S Y   T O   C H A N G E   I N P U T S
    // ==========================================
    // Format: {PID, Arrival, Burst, Priority}
    vector<Process> processes = {
        {1, 0, 10, 2, 0, 0, false},
        {2, 1, 5,  1, 0, 0, false}, // Higher priority (1 < 2)
        {3, 3, 2,  3, 0, 0, false},
        {4, 5, 20, 4, 0, 0, false}
    };
    // ==========================================

    int n = processes.size();
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int bestPriority = INT_MAX; // Looking for the lowest number

        // Find the process with highest priority among those that have arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                if (processes[i].priority < bestPriority) {
                    bestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
                // Optional Tie-breaker: If priorities match, choose the one that arrived first
                else if (processes[i].priority == bestPriority) {
                    if (processes[i].arrivalTime < processes[highestPriorityIndex].arrivalTime) {
                        highestPriorityIndex = i;
                    }
                }
            }
        }

        if (highestPriorityIndex != -1) {
            // Process found: Execute it fully (Non-preemptive)
            Process* p = &processes[highestPriorityIndex];
            
            // Calculate Completion Time
            int completionTime = currentTime + p->burstTime;
            
            // Calculate Metrics
            p->turnAroundTime = completionTime - p->arrivalTime;
            p->waitingTime = p->turnAroundTime - p->burstTime;
            
            // Update system state
            p->isCompleted = true;
            currentTime = completionTime;
            completed++;
        } else {
            // No process has arrived yet, CPU is idle
            currentTime++;
        }
    }

    // Output Results
    cout << "PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" 
             << processes[i].arrivalTime << "\t" 
             << processes[i].burstTime << "\t" 
             << processes[i].priority << "\t\t" 
             << processes[i].waitingTime << "\t" 
             << processes[i].turnAroundTime << endl;
    }

    return 0;
}
2. C Implementation
Using standard arrays and boolean flags.

C

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    bool isCompleted;
} Process;

int main() {
    // ==========================================
    // E A S Y   T O   C H A N G E   I N P U T S
    // ==========================================
    Process proc[] = {
        {1, 0, 10, 2}, // {PID, Arrival, Burst, Priority}
        {2, 1, 5,  1},
        {3, 3, 2,  3},
        {4, 5, 20, 4}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    // ==========================================

    // Initialize completion status
    for(int i=0; i<n; i++) proc[i].isCompleted = false;

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int minPriority = INT_MAX;

        // Search for highest priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].isCompleted) {
                if (proc[i].priority < minPriority) {
                    minPriority = proc[i].priority;
                    idx = i;
                }
                // Simple FCFS tie-breaker for same priority
                if (proc[i].priority == minPriority) {
                    if (proc[i].arrivalTime < proc[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Run process to completion immediately
            int finishTime = currentTime + proc[idx].burstTime;
            
            proc[idx].turnAroundTime = finishTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnAroundTime - proc[idx].burstTime;
            
            if (proc[idx].waitingTime < 0) proc[idx].waitingTime = 0; // Safety check

            proc[idx].isCompleted = true;
            completed++;
            currentTime = finishTime;
        } else {
            // Idle
            currentTime++;
        }
    }

    // Print
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", 
               proc[i].pid, 
               proc[i].arrivalTime, 
               proc[i].burstTime, 
               proc[i].priority,
               proc[i].waitingTime, 
               proc[i].turnAroundTime);
    }

    return 0;
}
3. Java Implementation
Java

public class NonPreemptivePriority {

    static class Process {
        int pid;
        int arrivalTime;
        int burstTime;
        int priority;
        int waitingTime;
        int turnAroundTime;
        boolean isCompleted;

        public Process(int pid, int arrivalTime, int burstTime, int priority) {
            this.pid = pid;
            this.arrivalTime = arrivalTime;
            this.burstTime = burstTime;
            this.priority = priority;
            this.isCompleted = false;
        }
    }

    public static void main(String[] args) {
        // ==========================================
        // E A S Y   T O   C H A N G E   I N P U T S
        // ==========================================
        Process[] processes = {
            new Process(1, 0, 10, 2), // PID, Arrival, Burst, Priority
            new Process(2, 1, 5, 1),
            new Process(3, 3, 2, 3),
            new Process(4, 5, 20, 4)
        };
        // ==========================================

        int n = processes.length;
        int currentTime = 0;
        int completed = 0;

        while (completed < n) {
            int idx = -1;
            int minPriority = Integer.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted) {
                    if (processes[i].priority < minPriority) {
                        minPriority = processes[i].priority;
                        idx = i;
                    }
                    if (processes[i].priority == minPriority) {
                         if (processes[i].arrivalTime < processes[idx].arrivalTime) {
                             idx = i;
                         }
                    }
                }
            }

            if (idx != -1) {
                // Execute process fully
                int finishTime = currentTime + processes[idx].burstTime;
                
                processes[idx].turnAroundTime = finishTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                
                processes[idx].isCompleted = true;
                completed++;
                currentTime = finishTime;
            } else {
                currentTime++;
            }
        }

        System.out.println("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround");
        for (Process p : processes) {
            System.out.println(p.pid + "\t" + 
                               p.arrivalTime + "\t" + 
                               p.burstTime + "\t" + 
                               p.priority + "\t\t" + 
                               p.waitingTime + "\t" + 
                               p.turnAroundTime);
        }
    }
}
Key Difference from Preemptive
In the previous preemptive code, inside the loop we did: currentTime++ (we only stepped 1 second at a time)

In this non-preemptive code, inside the loop we do: currentTime = currentTime + burstTime (we jump to the end of the process immediately)