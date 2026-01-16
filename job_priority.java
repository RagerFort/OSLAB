import java.util.Scanner;

public class job_priority {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int[] p = new int[20];
        int[] bt = new int[20];
        int[] wt = new int[20];
        int[] tat = new int[20];
        int i, k, n, temp;
        float wtavg, tatavg;

        System.out.print("\nEnter the number of processes -- ");
        n = sc.nextInt();

        // Input burst times
        for(i = 0; i < n; i++)
        {
            p[i] = i;
            System.out.print("Enter Burst Time for Process " + i + " -- ");
            bt[i] = sc.nextInt();
        }

        // Sort job by burst time (SJF - Bubble Sort)
        for(i = 0; i < n; i++)
        {
            for(k = i + 1; k < n; k++)
            {
                if(bt[i] > bt[k])
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

        for(i = 1; i < n; i++)
        {
            wt[i] = wt[i-1] + bt[i-1];
            tat[i] = tat[i-1] + bt[i];
            wtavg = wtavg + wt[i];
            tatavg = tatavg + tat[i];
        }

        // Display results
        System.out.println("\n\t PROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME");
        for(i = 0; i < n; i++)
        {
            System.out.printf("\n\t P%d\t\t%d\t\t%d\t\t%d", p[i], bt[i], wt[i], tat[i]);
        }

        System.out.printf("\n\nAverage Waiting Time -- %.2f", (wtavg / n));
        System.out.printf("\nAverage Turnaround Time -- %.2f", (tatavg / n));
        System.out.println();
        
        sc.close();
    }
}