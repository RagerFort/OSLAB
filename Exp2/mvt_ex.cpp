#include<iostream> // Load the tool that lets the program print messages and read user input
using namespace std; // Allow the program to use cout and cin without writing std:: every time

int main() { // This is the starting point — the program begins running here
    int ms, mp[10], i, temp, n = 0; // Declare storage for: total memory, a list of up to 10 process sizes, a loop counter, a temporary tracker for remaining memory, and a process counter starting at 0
    char ch = 'y'; // Set the continue flag to 'y' so the loop runs at least once

    cout << "\nEnter the total memory available (in Bytes): "; // Ask the user to type the total available memory
    cin >> ms; // Read and save the total memory
    temp = ms; // Copy the total memory into temp so we can track how much is left as we allocate

    for(i = 0; ch == 'y'; i++, n++) { // Keep looping as long as the user wants to add more processes — i tracks the index, n counts total processes
        cout << "\nEnter memory required for process " << i+1 << " (in Bytes): "; // Ask how much memory the next process needs
        cin >> mp[i]; // Read and save the process size into the list

        if(mp[i] <= temp) { // Check if the process fits within the remaining available memory
            cout << "\nMemory is allocated for Process " << i+1; // Confirm the process was successfully given memory
            temp = temp - mp[i]; // Subtract the process size from the remaining memory
        } else { // If the process is larger than the remaining memory
            cout << "\nMemory is Full"; // Notify the user that there is not enough memory left
            break; // Stop the loop since no more processes can be accommodated
        }

        cout << "\nDo you want to continue(y/n): "; // Ask the user if they want to add another process
        cin >> ch; // Read the answer — if the user types 'n', the loop will stop on the next check
    }

    cout << "\n\nTotal Memory Available: " << ms; // Print the original total memory the user entered
    cout << "\n\nPROCESS\t\tMEMORY ALLOCATED"; // Print the table header for the results

    for(i = 0; i < n; i++) // Loop through each successfully allocated process
        cout << "\n\t" << i+1 << "\t\t" << mp[i]; // Print each process number and the memory it was given

    cout << "\n\nTotal Memory Allocated is " << ms - temp; // Show total memory used by subtracting what is left from the total
    cout << "\nTotal External Fragmentation is " << temp; // Show the leftover memory that was never allocated — this is external fragmentation

    return 0; // Signal that the program finished successfully
}