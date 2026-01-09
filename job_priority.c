#include<stdio.h>

int main()
{
    int p[20], bt[20], wt[20], tat[20];
    int i, k, n, temp;
    float wtavg, tatavg;
    
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);
    
    // Input burst times for each process
    for(i = 0; i < n; i++)
    {
        p[i] = i;
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
    }
    
    // Sort job by burst time (Shortest Job First)
    // n is the number of processes
    // bt is the burst time array
    // p is the process ID array
    for(i = 0; i < n; i++) // Bubble Sort
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
    printf("\n\t PROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i = 0; i < n; i++)
    {
        printf("\n\t P%d\t\t%d\t\t%d\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }
    

    printf("\n\nAverage Waiting Time -- %.2f", wtavg / n);
    printf("\nAverage Turnaround Time -- %.2f", tatavg / n);
    printf("\n");
    
    return 0;
}