#include <iostream>
using namespace std;

int main() {
    int ms, temp, mp[10];
    int i = 0, n = 0;
    char ch = 'y';

    cout << "Enter the total memory available (in Bytes) -- ";
    cin >> ms;

    temp = ms;

    while(ch == 'y') {
        cout << "Enter memory required for process " << i+1 << " (in Bytes) -- ";
        cin >> mp[i];

        if(mp[i] <= temp) {
            cout << "Memory is allocated for Process " << i+1 << endl;
            temp -= mp[i];
        } else {
            cout << "Memory is Full\n";
            break;
        }

        i++;
        n++;

        cout << "Do you want to continue(y/n) -- ";
        cin >> ch;
    }

    cout << "\n\nTotal Memory Available -- " << ms;

    cout << "\n\nPROCESS\t\tMEMORY ALLOCATED";
    for(i = 0; i < n; i++) {
        cout << "\n" << i+1 << "\t\t" << mp[i];
    }

    cout << "\n\nTotal Memory Allocated is " << ms - temp;
    cout << "\nTotal External Fragmentation is " << temp;

    return 0;
}