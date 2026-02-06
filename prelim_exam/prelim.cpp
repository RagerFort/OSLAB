#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <cmath>

using namespace std;
// This program implements three CPU scheduling algorithms:
// 1. Round Robin (RR) with Recommended Time Quantum
// 2. Shortest Job First (SJF) - Non-Preemptive
// 3. Shortest Remaining Time First (SRTF) - Preemptive
// median = middle value in sorted list
// mean = sum of values / number of values


// Struct definition as requested
struct process {
    int pid; // Process ID
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time (for RR and SRTF)
    int ct;  // Completion Time 
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function prototypes
int rtq(const vector<process>& p); // Recommended Time Quantum
void rr(vector<process> p, int time_quantum); // Round Robin
void sjf(vector<process> p); // Shortest Job First
void srtf(vector<process> p); // Shortest Remaining Time First
void printTable(const vector<process>& p, string algName); // Helper to print tables

// 1. Calculate Recommended Time Quantum (Mean of Burst Time)
// Difference in mean and median is minimal for this dataset
// so we use mean for simplicity
// mean = sum(bt) / n
int rtq(const vector<process>& p) { // Recommended Time Quantum
    if (p.empty()) return 0; // Handle empty case
    double total_bt = 0; // Total Burst Time
    for (const auto& proc : p) { // Sum Burst Times
        total_bt += proc.bt; // Accumulate Burst Time
    }
    // Using Mean (Average) for recommended time quantum
    return round(total_bt / p.size()); // Round to nearest integer
}

// 2. Round Robin (RR)
// Preemptive Scheduling
void rr(vector<process> p, int time_quantum) { // Round Robin Scheduling
    int n = p.size(); // Number of processes
    int time = 0; // Current time
    int completed = 0; // Completed process count
    int index = 0;
    queue<int> q; // Process queue
    vector<bool> in_queue(n, false); // Track if process is in queue

    // Sort initially by Arrival Time for queue entry
    sort(p.begin(), p.end(), [](const process& a, const process& b) {
        return a.at < b.at;
    });

    // Push first process
    if (n > 0) {
        q.push(0); // Push first process index
        in_queue[0] = true; // Mark as in queue
        time = p[0].at;  // Start time at first arrival
    }

    while (completed < n) { // While not all processes are completed
        if (q.empty()) {
            // Jump time if queue is empty but processes remain
            for (int i = 0; i < n; i++) { // Find next arriving process
                if (p[i].rt > 0 && !in_queue[i]) { // Not completed and not in queue
                    time = p[i].at; // Jump time to arrival
                    q.push(i); // Push to queue
                    in_queue[i] = true; // Mark as in queue
                    break; // Exit after pushing one process
                }
            }
        }
        // Process at front of queue
        int idx = q.front(); 
        q.pop();

        int exec_time = min(time_quantum, p[idx].rt); // Execution time slice
        p[idx].rt -= exec_time; // Decrease remaining time
        time += exec_time;

        // Check for new arrivals during this execution
        for (int i = 0; i < n; i++) { // Check all processes
            if (!in_queue[i] && p[i].at <= time && p[i].rt > 0) { // Arrived and not in queue
                q.push(i); // Push to queue
                in_queue[i] = true; // Mark as in queue
            }
        }

        if (p[idx].rt == 0) { // Process completed
            p[idx].ct = time; // Set completion time
            p[idx].tat = p[idx].ct - p[idx].at; // Turnaround Time
            p[idx].wt = p[idx].tat - p[idx].bt; // Waiting Time
            completed++;
        } else {
            q.push(idx);
        }
    }

    // Sort back by PID for clean table output
    sort(p.begin(), p.end(), [](const process& a, const process& b) {
        return a.pid < b.pid;
    });

    printTable(p, "Round Robin (RR)");
}

// 3. Shortest Job First (SJF) - Non-Preemptive
void sjf(vector<process> p) {
    int n = p.size();
    int completed = 0;
    int time = 0;
    vector<bool> is_completed(n, false);
    vector<process> result = p; 

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Find process with min BT that has arrived
        for (int i = 0; i < n; i++) { // Compare all processes
            if (p[i].at <= time && !is_completed[i]) { // Arrived and not completed
                if (p[i].bt < min_bt) { // Minimum Burst Time
                    min_bt = p[i].bt; // Update min BT
                    idx = i; // Update index
                }
                // Tie-breaker: Arrival Time (optional, usually FCFS on tie)
                else if (p[i].bt == min_bt) { 
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) { // Found a process to execute
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at; // Turnaround Time (Completion - Arrival Time)
            p[idx].wt = p[idx].tat - p[idx].bt; // Waiting Time (Turnaround - Burst Time)

            // Update result vector to keep sorted by PID later
            result[idx] = p[idx]; 
            
            is_completed[idx] = true;
            completed++;
        } else {
            time++;
        }
    }
    
    // Pass the calculated results
    printTable(result, "Shortest Job First (SJF)");
}

// 4. Shortest Remaining Time First (SRTF)
void srtf(vector<process> p) {
    int n = p.size(); // Number of processes
    int completed = 0; // Completed process count
    int time = 0; // Current time
    int min_rt = 1e9; // 
    int shortest = -1;// Index of shortest process
    bool check = false; // Flag to check if a process is found

    // Find min arrival time to start
    int min_at = 1e9; // Initialize to large value
    for(const auto& x : p) min_at = min(min_at, x.at); // Minimum Arrival Time
    time = min_at; // Start time at first arrival

    while (completed != n) {
        // Find process with shortest remaining time among arrived
        shortest = -1; // Reset shortest index
        min_rt = 1e9; // Reset minimum remaining time
        
        for (int i = 0; i < n; i++) { // Check all processes
            if (p[i].at <= time && p[i].rt < min_rt && p[i].rt > 0) { // Check conditions if arrived and not completed
                min_rt = p[i].rt; // Update minimum remaining time
                shortest = i; // Update shortest index
                check = true; // Found a process
            }
        }

        if (!check || shortest == -1) { // No process found
            time++; // Increment time
            continue; // Skip to next iteration
        }

        // Execute for 1 unit
        p[shortest].rt--; // Decrease remaining time
        time++; // Increment time
        // If process is completed
        if (p[shortest].rt == 0) { // Process completed
            completed++; // Increment completed count
            check = false; // Reset check flag
            p[shortest].ct = time; // Set completion time
            p[shortest].tat = p[shortest].ct - p[shortest].at; // Turnaround Time = Completion - Arrival
            p[shortest].wt = p[shortest].tat - p[shortest].bt; // Waiting Time = Turnaround - Burst 
            if (p[shortest].wt < 0) p[shortest].wt = 0; // Ensure non-negative waiting time
        }
    }

    printTable(p, "Shortest Remaining Time First (SRTF)");
}

// Helper to print tables
void printTable(const vector<process>& p, string algName) {
    double total_tat = 0, total_wt = 0;
    
    cout << "\n" << algName << " Table" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
    cout << setw(5) << "PID" << setw(10) << "Arrival" << setw(10) << "Burst" 
         << setw(12) << "Completion" << setw(12) << "Turnaround" << setw(10) << "Waiting" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;

    for (const auto& proc : p) {
        total_tat += proc.tat;
        total_wt += proc.wt;
        cout << setw(5) << proc.pid 
             << setw(10) << proc.at 
             << setw(10) << proc.bt 
             << setw(12) << proc.ct 
             << setw(12) << proc.tat 
             << setw(10) << proc.wt << endl;
    }
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
    cout << "Avg Turnaround Time: " << fixed << setprecision(2) << (total_tat / p.size()) << endl;
    cout << "Avg Waiting Time:    " << fixed << setprecision(2) << (total_wt / p.size()) << endl;
    cout << endl;
}

int main() {
    // Hardcoded Input as requested
    // PIDs assumed to be sequential 1-8 based on input arrays
    int at_arr[] = {4, 2, 3, 6, 1, 5, 8, 7};
    int bt_arr[] = {53, 43, 18, 16, 44, 73, 99, 27};
    int n = 8;

    vector<process> processes;
    for(int i = 0; i < n; i++) { // Initialize processes
        process temp;
        temp.pid = i + 1; // PID from 1 to n
        temp.at = at_arr[i]; // Arrival Time
        temp.bt = bt_arr[i]; // Burst Time
        temp.rt = bt_arr[i]; // Remaining time starts equal to burst
        temp.ct = 0; // Initialize Completion Time
        temp.tat = 0; // Initialize Turnaround Time
        temp.wt = 0; // Initialize Waiting Time
        processes.push_back(temp); // Add to process list
    }

    // Calculate Recommended Time Quantum
    int recommended_tq = rtq(processes);
    cout << "Recommend Time quantum: " << recommended_tq << endl;

    // Sequential Order: RR, SJF, SRTF
    
    // 1. Round Robin
    rr(processes, recommended_tq); // Round Robin with recommended TQ

    // 2. SJF
    sjf(processes); // Shortest Job First

    // 3. SRTF
    srtf(processes); // Shortest Remaining Time First


    
    return 0;
}