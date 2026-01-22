import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

// A simple class to represent a Process
// Keeping this separate makes the data structure reusable
class ProcessRR {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;

    public ProcessRR(int id, int burstTime) {
        this.id = id;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
    }
}

public class round_robin {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<ProcessRR> processes = new ArrayList<>();

        // --- Input Section ---
        System.out.println("=== Round Robin Scheduler (Arrival Time = 0) ===");
        System.out.print("Enter number of processes: ");
        int n = validateInput(sc);

        for (int i = 0; i < n; i++) {
            System.out.print("Enter Burst Time for Process " + (i + 1) + ": ");
            int burst = validateInput(sc);
            processes.add(new ProcessRR(i + 1, burst));
        }

        System.out.print("Enter Time Quantum: ");
        int quantum = validateInput(sc);

        // --- Logic Section ---
        calculateRoundRobin(processes, quantum);

        // --- Output Section ---
        displayResults(processes);
        
        sc.close();
    }

    /**
     * core logic for Round Robin. 
     * This method is modular and can be reused in other parts of a larger system.
     */
    public static void calculateRoundRobin(List<ProcessRR> processes, int quantum) {
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();

        // Loop until all processes are finished
        while (completed < n) {
            boolean activeProcessFound = false;

            for (ProcessRR p : processes) {
                if (p.remainingTime > 0) {
                    activeProcessFound = true;
                    
                    if (p.remainingTime > quantum) {
                        // Process runs for the full quantum
                        currentTime += quantum;
                        p.remainingTime -= quantum;
                    } else {
                        // Process runs for the remaining time and finishes
                        currentTime += p.remainingTime;
                        p.remainingTime = 0;
                        
                        // Turnaround Time = Completion Time - Arrival Time (0)
                        p.turnAroundTime = currentTime;
                        
                        // Waiting Time = Turnaround Time - Burst Time
                        p.waitingTime = p.turnAroundTime - p.burstTime;
                        
                        completed++;
                    }
                }
            }
            // Safety break if no processes are left but logic thinks otherwise
            if (!activeProcessFound) break; 
        }
    }

    // Helper method to display the table clearly
    public static void displayResults(List<ProcessRR> processes) {
        System.out.println("\n-------------------------------------------------------");
        System.out.printf("%-10s %-15s %-15s %-15s\n", "Process", "Burst Time", "Waiting Time", "Turnaround Time");
        System.out.println("-------------------------------------------------------");

        double totalWait = 0;
        double totalTurn = 0;

        for (ProcessRR p : processes) {
            System.out.printf("P%-9d %-15d %-15d %-15d\n", p.id, p.burstTime, p.waitingTime, p.turnAroundTime);
            totalWait += p.waitingTime;
            totalTurn += p.turnAroundTime;
        }

        System.out.println("-------------------------------------------------------");
        System.out.printf("Average Waiting Time:    %.2f\n", (totalWait / processes.size()));
        System.out.printf("Average Turnaround Time: %.2f\n", (totalTurn / processes.size()));
    }
    
    // Helper to ensure non-negative input
    private static int validateInput(Scanner sc) {
        int input = -1;
        while (input < 0) {
            if (sc.hasNextInt()) {
                input = sc.nextInt();
                if(input < 0) System.out.print("Please enter a positive number: ");
            } else {
                System.out.print("Invalid input. Please enter a number: ");
                sc.next(); // clear invalid input
            }
        }
        return input;
    }
}