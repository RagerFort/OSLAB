using System;
using System.Collections.Generic;
using System.Linq;


public class Process
{
    public int Id { get; set; }             // Process ID
    public int BurstTime { get; set; }      // Total work needed
    public int RemainingTime { get; set; }  // Time left to finish
    public int ArrivalTime { get; set; }    // When it arrived
    public int WaitingTime { get; set; }    // Time spent waiting
    public int TurnAroundTime { get; set; } // Total time in system
    public int CompletionTime { get; set; } // When it finished
}

class RoundRobin
{
    static void Main(string[] args)
    {
        // "Easy to Change": Using a List instead of an array so you can add 
        // as many processes as you want without setting a fixed limit.
        List<Process> processes = new List<Process>();
        
        int quantum;
        int currentTime = 0;
        int completedCount = 0;

        // --- INPUT SECTION ---
        Console.Write("Enter number of processes: ");
        int n = int.Parse(Console.ReadLine());

        Console.Write("Enter Time Quantum: ");
        quantum = int.Parse(Console.ReadLine());

        for (int i = 0; i < n; i++)
        {
            Process p = new Process();
            p.Id = i + 1;

            Console.WriteLine($"\n--- Process {p.Id} ---");
            Console.Write("Enter Arrival Time: ");
            p.ArrivalTime = int.Parse(Console.ReadLine());

            Console.Write("Enter Burst Time: ");
            p.BurstTime = int.Parse(Console.ReadLine());

            // Initially, remaining time is exactly the burst time
            p.RemainingTime = p.BurstTime;

            processes.Add(p);
        }

        // --- SCHEDULING LOGIC ---
        Console.WriteLine("\n--- Starting Round Robin Scheduling ---");

        // Keep looping until we have completed as many processes as we started with
        while (completedCount < n)
        {
            bool isIdle = true; // Tracks if the CPU did any work this cycle

            // Iterate through the list of processes
            foreach (var p in processes)
            {
                // Check if process has arrived in the timeline AND is not finished
                if (p.ArrivalTime <= currentTime && p.RemainingTime > 0)
                {
                    isIdle = false; // CPU is busy

                    if (p.RemainingTime > quantum)
                    {
                        // Process runs for the full quantum
                        currentTime += quantum;
                        p.RemainingTime -= quantum;
                    }
                    else
                    {
                        // Process finishes (needs less than or equal to quantum)
                        currentTime += p.RemainingTime;
                        p.RemainingTime = 0;

                        // CALCULATION: Process is complete
                        completedCount++;
                        p.CompletionTime = currentTime;
                        p.TurnAroundTime = p.CompletionTime - p.ArrivalTime;
                        p.WaitingTime = p.TurnAroundTime - p.BurstTime;
                    }
                }
            }

            // If no process was ready (e.g., all remaining processes arrive later),
            // simply move time forward to prevent an infinite loop.
            if (isIdle)
            {
                currentTime++;
            }
        }

        // --- OUTPUT SECTION ---
        Console.WriteLine("\n-----------------------------------------------------------------------");
        Console.WriteLine("ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        Console.WriteLine("-----------------------------------------------------------------------");

        double totalWait = 0;
        double totalTurn = 0;

        // We use .OrderBy(p => p.Id) to print them in ID order (1, 2, 3) 
        // rather than the order they finished in.
        foreach (var p in processes.OrderBy(x => x.Id))
        {
            Console.WriteLine($"{p.Id}\t{p.ArrivalTime}\t{p.BurstTime}\t{p.CompletionTime}\t\t{p.TurnAroundTime}\t\t{p.WaitingTime}");
            
            totalWait += p.WaitingTime;
            totalTurn += p.TurnAroundTime;
        }

        Console.WriteLine("-----------------------------------------------------------------------");
        Console.WriteLine($"Average Waiting Time: {totalWait / n:F2}");
        Console.WriteLine($"Average Turnaround Time: {totalTurn / n:F2}");
        
        // Prevent console from closing immediately
        Console.WriteLine("\nPress any key to exit...");
        Console.ReadKey();
    }
}