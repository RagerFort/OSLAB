#include<iostream> // Load the tool that lets the program print messages and read user input
using namespace std; // Allow the program to use cout and cin without writing std:: every time

int main() { // This is the starting point — the program begins running here
    int ms, bs, nob, ef, n, mp[10], tif = 0; // Declare storage for: total memory, block size, number of blocks, external fragmentation, number of processes, a list of up to 10 process sizes, and total internal fragmentation starting at 0
    int i, p = 0; // Declare a loop counter i, and p to track how many blocks have been used starting at 0

    cout << "Enter the total memory available (in Bytes): "; // Ask the user to type the total memory
    cin >> ms; // Read and save the total memory the user typed
    cout << "Enter the block size (in Bytes): "; // Ask the user to type how big each memory block should be
    cin >> bs; // Read and save the block size

    nob = ms / bs; // Calculate how many equal blocks fit inside the total memory by dividing
    ef = ms - nob * bs; // Calculate the leftover memory that cannot form a complete block — this is external fragmentation

    cout << "\nEnter the number of processes: "; // Ask the user how many processes they want to enter
    cin >> n; // Read and save the number of processes

    for(i = 0; i < n; i++) { // Repeat the following for each process the user entered
        cout << "Enter memory required for process " << i+1 << " (in Bytes): "; // Ask how much memory each process needs
        cin >> mp[i]; // Read and save that process's memory requirement into the list
    }

    cout << "\nNo. of Blocks available in memory: " << nob; // Display how many blocks are available
    cout << "\n\nPROCESS\tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION"; // Print the table header for the results

    for(i = 0; i < n && p < nob; i++) { // Go through each process, but stop early if all blocks are already filled
        cout << "\n " << i+1 << "\t\t" << mp[i]; // Print the process number and how much memory it needs
        if(mp[i] > bs) // Check if the process needs more memory than a single block can provide
            cout << "\t\tNO\t\t---"; // If yes, reject the process and print NO — it cannot be allocated
        else { // If the process fits within the block size
            cout << "\t\tYES\t\t" << bs - mp[i]; // Print YES and show the leftover unused space inside the block
            tif += bs - mp[i]; // Add that leftover unused space to the running total of internal fragmentation
            p++; // Mark this block as used by increasing the block usage counter
        }
    }

    if(i < n) // Check if there are still unallocated processes remaining after the loop ended
        cout << "\nMemory is Full, Remaining Processes cannot be accommodated"; // Notify the user that memory ran out before all processes were handled

    cout << "\n\nTotal Internal Fragmentation is " << tif; // Print the total wasted space found inside all allocated blocks
    cout << "\nTotal External Fragmentation is " << ef; // Print the leftover memory that could not form a usable block

    return 0; // Signal that the program finished successfully
}