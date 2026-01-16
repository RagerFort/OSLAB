#include <stdio.h>

int main()
{
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0, tatavg = 0;

    // Ask for number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    // Input Burst Times
    for(i = 0; i < n; i++)
    {
        printf("Enter Burst Time for Process %d: ", i);
        scanf("%d", &bt[i]);
    }

    // First process always has 0 waiting time
    wt[0] = 0;
    tat[0] = bt[0]; // For the first process, TAT = Burst Time (since WT is 0)

    // Calculate Waiting Time and Turnaround Time for the rest
    for(i = 1; i < n; i++)
    {
        // Waiting Time = Previous Process Waiting Time + Previous Process Burst Time
        wt[i] = wt[i-1] + bt[i-1];
        
        // Turnaround Time = Waiting Time + Burst Time
        tat[i] = wt[i] + bt[i];
    }

    // Calculate Totals for Averages
    for(i = 0; i < n; i++)
    {
        wtavg += wt[i];
        tatavg += tat[i];
    }

    // Print Table
    printf("\n----------------------------------------------------------------");
    printf("\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME\n");
    printf("----------------------------------------------------------------");
    
    for(i = 0; i < n; i++)
    {
        printf("\n P%d \t\t %-10d \t %-10d \t %-10d", i, bt[i], wt[i], tat[i]);
    }
    
    printf("\n----------------------------------------------------------------");
    printf("\n\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

    return 0;
}