#include <iostream> // For input-output operations
#include <iomanip> // For table formatting (setw, setprecision)
#include <string> // For to_string

using namespace std;

int main()
{
    int p[20];
    float bt[20], wt[20], tat[20];
    int i, k, n;
    int temp_p;
    float temp_bt;
    float wtavg, tatavg;

    n = 5;  // Number of processes

    // Hardcoded burst times
    bt[0] = 50.54;
    bt[1] = 10.11;
    bt[2] = 33.34;
    bt[3] = 2.5;
    bt[4] = 101.1;

    // Set process IDs
    for(i = 0; i < n; i++)
    {
        p[i] = i;
    }

    // Sort by burst time (SJF)
    for(i = 0; i < n; i++)
    {
        for(k = i + 1; k < n; k++) //
        {
            if(bt[i] > bt[k])
            {
                // Swap burst times
                // k is index of the minimum element
                // i is the current position
                temp_bt = bt[i];  // Save bt[i]
                bt[i] = bt[k];    // bt[i] gets bt[k]
                bt[k] = temp_bt;  // bt[k] gets original bt[i]

                // Swap process IDs
                temp_p = p[i];
                p[i] = p[k];
                p[k] = temp_p;
            }
        }
    }

    // Calculate waiting time and turnaround time
    wt[0] = 0;
    tat[0] = bt[0];

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i-1] + bt[i-1]; // Waiting time is sum of previous WT and BT
        tat[i] = tat[i-1] + bt[i]; // Turnaround time is sum of previous TAT and current BT
    }

    // Calculate averages
    wtavg = 0;
    tatavg = 0;
    
    for(i = 0; i < n; i++)
    {
        wtavg += wt[i]; // Accumulate total waiting time
        tatavg += tat[i]; // Accumulate total turnaround time
    }

    // Display results
    cout << fixed << setprecision(2);
    cout << "--------+-----------+-------------+-----------------+-----------------\n";
    cout << "Process | Burst Time| Waiting Time| Turnaround Time | Completion Time \n";
    cout << "--------+-----------+-------------+-----------------+-----------------\n";

    // THIS LINE PRINTS THE DETAILS OF EACH PROCESS
    for (int i = 0; i < n; i++) {
        cout << setw(7) << p[i] << " | "
             << setw(9) << bt[i] << " | "
             << setw(11) << wt[i] << " | "
             << setw(15) << tat[i] << " | "
             << setw(15) << tat[i] << "\n";
    }
    // THIS LINE PRINTS THE AVERAGE WAITING TIME AND TURNAROUND TIME
    cout << "--------+-----------+-------------+-----------------+-----------------\n";
    cout << "\n-----------------------------------------------------\n";
    cout << "Average Waiting Time: " << (wtavg / n) << " ms\n";
    cout << "Average Turnaround Time: " << (tatavg / n) << " ms\n";
    cout << "-----------------------------------------------------\n";

    return 0;
}