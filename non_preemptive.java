import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class ProcessPriority {
    int id;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;

    public ProcessPriority(int id, int burstTime, int priority) {
        this.id = id;
        this.burstTime = burstTime;
        this.priority = priority;
    }
}

public class non_preemptive {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<ProcessPriority> processes = new ArrayList<>();

        // --- Input Section ---
        System.out.println("=== Non-Preemptive Priority Scheduler ===");
        System.out.print("Enter number of processes: ");
        int n = validateInput(sc);

        for (int i = 0; i < n; i++) {
            System.out.println("Details for Process " + (i + 1) + ":");
            System.out.print("  Burst Time: ");
            int burst = validateInput(sc);
            System.out.print("  Priority (Lower value = Higher Priority): ");
            int priority = validateInput(sc);
            processes.add(new ProcessPriority(i + 1, burst, priority));
        }

        // --- Logic Section  ---
        runPriorityScheduling(processes);

        // --- Output Section ---
        displayResults(processes);
        
        sc.close();
    }

    /**
     * Core logic: Sorts by priority and calculates times.
     */
    public static void runPriorityScheduling(List<ProcessPriority> processes) {
        // 1. Sort the processes based on Priority
        // Using a custom comparator allows this logic to be easily tweaked
        Collections.sort(processes, new Comparator<ProcessPriority>() {
            @Override
            public int compare(ProcessPriority p1, ProcessPriority p2) {
                // Ascending order: Lower number = Higher priority
                return Integer.compare(p1.priority, p2.priority);
            }
        });

        // 2. Calculate Waiting and Turnaround times
        int currentTime = 0;
        for (ProcessPriority p : processes) {
            // Since Arrival Time is 0, Waiting Time is simply the time elapsed so far
            p.waitingTime = currentTime;
            
            // Turnaround Time = Waiting Time + Burst Time
            p.turnAroundTime = p.waitingTime + p.burstTime;
            
            // Update current time clock
            currentTime += p.burstTime;
        }
    }

    public static void displayResults(List<ProcessPriority> processes) {
        System.out.println("\n----------------------------------------------------------------------");
        System.out.printf("%-10s %-10s %-15s %-15s %-15s\n", "Process", "Priority", "Burst Time", "Waiting Time", "Turnaround Time");
        System.out.println("----------------------------------------------------------------------");

        double totalWait = 0;
        double totalTurn = 0;

        for (ProcessPriority p : processes) {
            System.out.printf("P%-9d %-10d %-15d %-15d %-15d\n", p.id, p.priority, p.burstTime, p.waitingTime, p.turnAroundTime);
            totalWait += p.waitingTime;
            totalTurn += p.turnAroundTime;
        }

        System.out.println("----------------------------------------------------------------------");
        System.out.printf("Average Waiting Time:    %.2f\n", (totalWait / processes.size()));
        System.out.printf("Average Turnaround Time: %.2f\n", (totalTurn / processes.size()));
    }

    private static int validateInput(Scanner sc) {
        int input = -1;
        while (input < 0) {
            if (sc.hasNextInt()) {
                input = sc.nextInt();
                if(input < 0) System.out.print("Please enter a positive number: ");
            } else {
                System.out.print("Invalid input. Please enter a number: ");
                sc.next(); 
            }
        }
        return input;
    }
}