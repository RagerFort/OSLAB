Here are implementations for the Shortest Remaining Time First (SRTF) scheduling algorithm. This is the preemptive version of Shortest Job First (SJF).

In this algorithm:

The CPU is assigned to the process with the smallest remaining burst time.

If a new process arrives with a shorter burst time than the current running process, the CPU is preempted (taken away) and given to the new process.

All examples use hardcoded input variables at the top of the main function so they are easy for you to modify.

1. C++ Implementation
This version uses std::vector and structs for clean organization.

C++

`#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid; // Process ID
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

int main() {
    // ==========================================
    // E A S Y   T O   C H A N G E   I N P U T S
    // ==========================================
    // Format: {Process ID, Arrival Time, Burst Time}
    // Note: Completion/Waiting/TurnAround are calculated automatically.
    vector<Process> processes = {
        {1, 0, 8, 0, 0, 0, 0},
        {2, 1, 4, 0, 0, 0, 0},
        {3, 2, 9, 0, 0, 0, 0},
        {4, 3, 5, 0, 0, 0, 0}
    };
    // ==========================================

    int n = processes.size();
    
    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    int shortestIndex = -1;
    int minRemainingTime = INT_MAX;
    bool found = false;

    // Run until all processes are completed
    while (completed != n) {
        
        // Find process with minimum remaining time among those that have arrived
        minRemainingTime = INT_MAX;
        shortestIndex = -1;
        found = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime < minRemainingTime) {
                    minRemainingTime = processes[i].remainingTime;
                    shortestIndex = i;
                    found = true;
                }
                // If remaining times are equal, pick the one that arrived first (optional tie-breaker)
                if (processes[i].remainingTime == minRemainingTime) {
                    if (processes[i].arrivalTime < processes[shortestIndex].arrivalTime) {
                        shortestIndex = i;
                    }
                }
            }
        }

        if (found) {
            // Process the chosen process for 1 unit of time
            processes[shortestIndex].remainingTime--;
            currentTime++;

            // Check if process is finished
            if (processes[shortestIndex].remainingTime == 0) {
                completed++;
                processes[shortestIndex].completionTime = currentTime;
                processes[shortestIndex].turnAroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
                processes[shortestIndex].waitingTime = processes[shortestIndex].turnAroundTime - processes[shortestIndex].burstTime;
            }
        } else {
            // CPU is idle
            currentTime++;
        }
    }

    // Output Results
    cout << "PID\tArrival\tBurst\tWaiting\tTurnaround" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" 
             << processes[i].arrivalTime << "\t" 
             << processes[i].burstTime << "\t" 
             << processes[i].waitingTime << "\t" 
             << processes[i].turnAroundTime << endl;
    }

    return 0;
}`
2. C Implementation
This version uses standard arrays and manual index handling, compatible with standard C compilers.

C

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
} Process;

int main() {
    // ==========================================
    // E A S Y   T O   C H A N G E   I N P U T S
    // ==========================================
    // You can add more processes to this array
    Process proc[] = {
        {1, 0, 8}, // {PID, Arrival, Burst}
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    // ==========================================

    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        proc[i].remainingTime = proc[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    int shortestIndex = -1;
    int minRemainingTime = INT_MAX;
    bool check = false;

    // Main scheduling loop
    while (completed != n) {
        
        // Find process with shortest remaining time among arrived processes
        minRemainingTime = INT_MAX;
        check = false;
        shortestIndex = -1;

        for (int i = 0; i < n; i++) {
            if ((proc[i].arrivalTime <= currentTime) && (proc[i].remainingTime > 0) && (proc[i].remainingTime < minRemainingTime)) {
                minRemainingTime = proc[i].remainingTime;
                shortestIndex = i;
                check = true;
            }
        }

        if (!check) {
            // No process available yet, increment time
            currentTime++;
            continue;
        }

        // Execute the found process for 1 unit of time
        proc[shortestIndex].remainingTime--;
        
        // Note: In a real simulation, we increment time after execution
        currentTime++;

        // If process is finished
        if (proc[shortestIndex].remainingTime == 0) {
            completed++;
            
            // Calculate Completion Time (CT), Turnaround (TAT), Waiting (WT)
            int finishTime = currentTime;
            proc[shortestIndex].turnAroundTime = finishTime - proc[shortestIndex].arrivalTime;
            proc[shortestIndex].waitingTime = proc[shortestIndex].turnAroundTime - proc[shortestIndex].burstTime;
            
            // Handle negative waiting time (should not happen in valid logic but good for safety)
            if (proc[shortestIndex].waitingTime < 0) 
                proc[shortestIndex].waitingTime = 0;
        }
    }

    // Print table
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
3. Java Implementation
Uses a simple static main method and a Process class.

Java

public class SRTF {

    static class Process {
        int pid;
        int arrivalTime;
        int burstTime;
        int remainingTime;
        int waitingTime;
        int turnAroundTime;
        int completionTime;

        public Process(int pid, int arrivalTime, int burstTime) {
            this.pid = pid;
            this.arrivalTime = arrivalTime;
            this.burstTime = burstTime;
            this.remainingTime = burstTime; // Initially same as burst
        }
    }

    public static void main(String[] args) {
        // ==========================================
        // E A S Y   T O   C H A N G E   I N P U T S
        // ==========================================
        Process[] processes = {
            new Process(1, 0, 8), // PID, Arrival, Burst
            new Process(2, 1, 4),
            new Process(3, 2, 9),
            new Process(4, 3, 5)
        };
        // ==========================================

        int n = processes.length;
        int currentTime = 0;
        int completed = 0;
        int minRemainingTime = Integer.MAX_VALUE;
        int shortestIndex = -1;
        boolean check = false;

        // Loop until all processes are complete
        while (completed != n) {
            
            minRemainingTime = Integer.MAX_VALUE;
            shortestIndex = -1;
            check = false;

            // Select the process with smallest remaining time
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    if (processes[i].remainingTime < minRemainingTime) {
                        minRemainingTime = processes[i].remainingTime;
                        shortestIndex = i;
                        check = true;
                    }
                }
            }

            if (!check) {
                currentTime++;
                continue;
            }

            // Execute process
            processes[shortestIndex].remainingTime--;
            currentTime++;

            // If finished
            if (processes[shortestIndex].remainingTime == 0) {
                completed++;
                processes[shortestIndex].completionTime = currentTime;
                processes[shortestIndex].turnAroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
                processes[shortestIndex].waitingTime = processes[shortestIndex].turnAroundTime - processes[shortestIndex].burstTime;
            }
        }

        // Display
        System.out.println("PID\tArrival\tBurst\tWaiting\tTurnaround");
        for (int i = 0; i < n; i++) {
            System.out.println(processes[i].pid + "\t" +
                               processes[i].arrivalTime + "\t" +
                               processes[i].burstTime + "\t" +
                               processes[i].waitingTime + "\t" +
                               processes[i].turnAroundTime);
        }
    }
}
How to use this for other algorithms?
If you need Preemptive Priority Scheduling instead of SRTF, the logic is nearly identical. You only need to change the comparison condition inside the while loop:

Current (SRTF): if (processes[i].remainingTime < minRemainingTime)

Priority Algo: if (processes[i].priority < highestPriority)