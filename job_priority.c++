#include <iostream>
#include <iomanip> // Used for setprecision

using namespace std;

int main()
{
    int p[20], bt[20], wt[20], tat[20];
    int i, k, n, temp;
    float wtavg, tatavg;

    cout << "\nEnter the number of processes -- ";
    cin >> n;

    // Input burst times
    for(i = 0; i < n; i++)
    {
        p[i] = i;
        cout << "Enter Burst Time for Process " << i << " -- ";
        cin >> bt[i];
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
    cout << "\n\t PROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for(i = 0; i < n; i++)
    {
        cout << "\n\t P" << p[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    }

    // Output formatting for decimals
    cout << fixed << setprecision(2);
    
    cout << "\n\nAverage Waiting Time -- " << (wtavg / n);
    cout << "\nAverage Turnaround Time -- " << (tatavg / n);
    cout << "\n";

    return 0;
}