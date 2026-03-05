#include<iostream>
using namespace std;

class MemoryMVT {
private:
    int totalMemory, processes[10], numProcesses, remaining;

public:
    MemoryMVT() {
        numProcesses = 0;
        remaining = 0;
    }

    void getInput() {
        cout << "\nEnter the total memory available (in Bytes): ";
        cin >> totalMemory;
        remaining = totalMemory;
    }

    void allocate() {
        char ch = 'y';

        for(int i = 0; ch == 'y'; i++, numProcesses++) {
            cout << "\nEnter memory required for process " << i+1 << " (in Bytes): ";
            cin >> processes[i];

            if(processes[i] <= remaining) {
                cout << "\nMemory is allocated for Process " << i+1;
                remaining -= processes[i];
            } else {
                cout << "\nMemory is Full";
                break;
            }

            cout << "\nDo you want to continue(y/n): ";
            cin >> ch;
        }
    }

    void displayResults() {
        cout << "\n\nTotal Memory Available: " << totalMemory;
        cout << "\n\nPROCESS\t\tMEMORY ALLOCATED";

        for(int i = 0; i < numProcesses; i++)
            cout << "\n\t" << i+1 << "\t\t" << processes[i];

        cout << "\n\nTotal Memory Allocated is " << totalMemory - remaining;
        cout << "\nTotal External Fragmentation is " << remaining;
    }
};

int main() {
    MemoryMVT mem;
    mem.getInput();
    mem.allocate();
    mem.displayResults();
    return 0;
}