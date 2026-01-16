using System;

class Program
{
    static void Main()
    {
        int[] p = new int[20];
        int[] bt = new int[20];
        int[] wt = new int[20];
        int[] tat = new int[20];
        int i, k, n, temp;
        float wtavg, tatavg;

        Console.Write("\nEnter the number of processes -- ");
        n = int.Parse(Console.ReadLine());

        // Input burst times
        for (i = 0; i < n; i++)
        {
            p[i] = i;
            Console.Write($"Enter Burst Time for Process {i} -- ");
            bt[i] = int.Parse(Console.ReadLine());
        }

        // Sort job by burst time (SJF - Bubble Sort)
        for (i = 0; i < n; i++)
        {
            for (k = i + 1; k < n; k++)
            {
                if (bt[i] > bt[k])
                {
                    // Swap burst times
                    temp = bt[i];
                    bt[i] = bt[k];
                    bt[k] = temp;

                    // Swap process IDs
                    temp = p[i];
                    p[i] = p[k];
                    p[k] = temp;
                }
            }
        }

        // Calculate waiting time and turnaround time
        wt[0] = 0;
        tat[0] = bt[0];
        wtavg = 0;
        tatavg = bt[0];

        for (i = 1; i < n; i++)
        {
            wt[i] = wt[i - 1] + bt[i - 1];
            tat[i] = tat[i - 1] + bt[i];
            wtavg = wtavg + wt[i];
            tatavg = tatavg + tat[i];
        }

        // Display results
        Console.WriteLine("\n\t PROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
        for (i = 0; i < n; i++)
        {
            Console.WriteLine($"\n\t P{p[i]}\t\t{bt[i]}\t\t{wt[i]}\t\t{tat[i]}");
        }

        Console.WriteLine($"\n\nAverage Waiting Time -- {(wtavg / n):F2}");
        Console.WriteLine($"Average Turnaround Time -- {(tatavg / n):F2}");
        Console.WriteLine();
    }
}