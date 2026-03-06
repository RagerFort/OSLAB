#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ===== CONFIGURATION - Easy to Change =====
const int NUM_QUEUES = 3;           // Number of priority queues
const int TIME_QUANTUM = 4;         // Time slice for each queue
const int QUEUE_BOOST_TIME = 8;     // Time before boosting all processes to highest priority
const int PRIORITY_BOOST = 1;       // Priority boost amount when switching queues

// ===== PROCESS STRUCTURE =====
struct Process {
    int pid;                // Process ID
    int burst_time;         // CPU time needed
    int arrival_time;       // When process arrives
    int time_in_system;     // Total time in system
    int current_queue;      // Current priority queue level
    int start_time;         // When process starts execution
    int end_time;           // When process completes
};

// ===== MLFQ SCHEDULER CLASS =====
class MLFQ {
private:
    vector<queue<Process>> queues;  // Priority queues
    int current_time;
    int total_boost_time;
    
public:
    MLFQ() : current_time(0), total_boost_time(0) {
        queues.resize(NUM_QUEUES);
    }
    
    // Add process to highest priority queue
    void addProcess(Process p) {
        p.current_queue = 0;
        p.start_time = -1;
        queues[0].push(p);
    }
    
    // Execute and schedule processes
    void schedule() {
        cout << "\n=== MLFQ Scheduling ===\n";
        vector<Process> completed;
        
        while (true) {
            // Check if all queues are empty
            bool all_empty = true;
            for (int i = 0; i < NUM_QUEUES; i++) {
                if (!queues[i].empty()) all_empty = false;
            }
            if (all_empty) break;
            
            // Boost all processes after QUEUE_BOOST_TIME
            if (current_time % QUEUE_BOOST_TIME == 0 && current_time > 0) {
                boostAllProcesses();
                cout << ">> Priority boost at time " << current_time << "\n";
            }
            
            // Find highest priority non-empty queue
            Process current = {-1, 0, 0, 0, -1, 0, 0};
            int queue_level = -1;
            
            for (int i = 0; i < NUM_QUEUES; i++) {
                if (!queues[i].empty()) {
                    current = queues[i].front();
                    queue_level = i;
                    queues[i].pop();
                    break;
                }
            }
            
            if (queue_level == -1) {
                current_time++;
                continue;
            }
            
            // Set start time on first execution
            if (current.start_time == -1) {
                current.start_time = current_time;
            }
            
            // Execute for min(TIME_QUANTUM, remaining burst time)
            int exec_time = min(TIME_QUANTUM, current.burst_time);
            current.burst_time -= exec_time;
            current_time += exec_time;
            
            cout << "Time " << current_time << ": PID " << current.pid 
                 << " (Q" << queue_level << ") executed for " << exec_time << "ms\n";
            
            // Process completed
            if (current.burst_time == 0) {
                current.end_time = current_time;
                current.time_in_system = current.end_time - current.arrival_time;
                completed.push_back(current);
                cout << "   >> PID " << current.pid << " COMPLETED\n";
            }
            // Move to next queue if not highest priority
            else if (queue_level < NUM_QUEUES - 1) {
                current.current_queue++;
                queues[queue_level + 1].push(current);
            }
            // Keep in same queue if already at lowest priority
            else {
                queues[queue_level].push(current);
            }
        }
        
        // Print statistics
        printStats(completed);
    }
    
private:
    // Boost all processes to highest priority
    void boostAllProcesses() {
        queue<Process> all_processes;
        
        for (int i = 0; i < NUM_QUEUES; i++) {
            while (!queues[i].empty()) {
                Process p = queues[i].front();
                queues[i].pop();
                p.current_queue = 0;
                all_processes.push(p);
            }
        }
        
        while (!all_processes.empty()) {
            queues[0].push(all_processes.front());
            all_processes.pop();
        }
    }
    
    // Print scheduling statistics
    void printStats(vector<Process>& completed) {
        cout << "\n=== Completion Statistics ===\n";
        double avg_wait = 0, avg_turnaround = 0;
        
        for (const auto& p : completed) {
            int wait_time = p.start_time - p.arrival_time;
            cout << "PID " << p.pid << ": Wait=" << wait_time 
                 << "ms, Turnaround=" << p.time_in_system << "ms\n";
            avg_wait += wait_time;
            avg_turnaround += p.time_in_system;
        }
        
        if (!completed.empty()) {
            cout << "\nAverage Wait Time: " << avg_wait / completed.size() << "ms\n";
            cout << "Average Turnaround Time: " << avg_turnaround / completed.size() << "ms\n";
        }
    }
};

// ===== MAIN =====
int main() {
    MLFQ scheduler;
    
    // Add test processes - Easy to modify
    scheduler.addProcess({1, 8, 0, 0, 0, 0, 0});
    scheduler.addProcess({2, 4, 1, 0, 0, 0, 0});
    scheduler.addProcess({3, 2, 2, 0, 0, 0, 0});
    scheduler.addProcess({4, 5, 3, 0, 0, 0, 0});
    
    scheduler.schedule();
    
    return 0;
}