#include <iostream>
#include <iomanip> // Used for table formatting (setw)

using namespace std;

int main()
{
    int bt[20], wt[20], tat[20], i, n;
    float wtavg = 0, tatavg = 0;

    n = 10;  // Number of processes

    // Hardcoded Burst Times
    bt[0] = 3;
    bt[1] = 5;
    bt[2] = 4;
    bt[3] = 3;
    bt[4] = 2;
    bt[5] = 1;
    bt[6] = 0;
    bt[7] = 7;
    bt[8] = 8;
    bt[9] = 1;

    // First process always has 0 waiting time
    wt[0] = 0;
    tat[0] = bt[0]; // TAT = Burst Time for first process

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
    cout << "\n----------------------------------------------------------------";
    cout << "\n PROCESS \t BURST TIME \t WAITING TIME \t TURNAROUND TIME\n";
    cout << "----------------------------------------------------------------";
    
    for(i = 0; i < n; i++)
    {
        cout << "\n P" << i 
             << "\t\t " << left << setw(10) << bt[i] 
             << " \t " << left << setw(10) << wt[i] 
             << " \t " << left << setw(10) << tat[i];
    }
    
    cout << "\n----------------------------------------------------------------";
    
    // setprecision(2) ensures 2 decimal places, fixed ensures standard notation
    cout << fixed << setprecision(2);
    cout << "\n\nAverage Waiting Time(WT): " << (wtavg / n)<< "ms";
    cout << "\nAverage Turnaround Time(TAT): " << (tatavg / n) <<"ms" << endl;

    return 0;
}