#include <iostream>
using namespace std;

class MVT {
private:
    int ms, temp, mp[10], n;

public:
    void input() {
        cout << "Enter the total memory available (in Bytes) -- ";
        cin >> ms;
        temp = ms;
        n = 0;
    }

    void allocate() {
        char ch = 'y';

        while(ch == 'y') {
            cout << "Enter memory required for process " << n+1 << " (in Bytes) -- ";
            cin >> mp[n];

            if(mp[n] <= temp) {
                cout << "Memory is allocated for Process " << n+1 << endl;
                temp -= mp[n];
            } else {
                cout << "Memory is Full\n";
                break;
            }

            n++;
            cout << "Do you want to continue(y/n) -- ";
            cin >> ch;
        }
    }

    void display() {
        cout << "\n\nTotal Memory Available -- " << ms;

        cout << "\n\nPROCESS\t\tMEMORY ALLOCATED";
        for(int i = 0; i < n; i++) {
            cout << "\n" << i+1 << "\t\t" << mp[i];
        }

        cout << "\n\nTotal Memory Allocated is " << ms - temp;
        cout << "\nTotal External Fragmentation is " << temp;
    }
};

int main() {
    MVT obj;
    obj.input();
    obj.allocate();
    obj.display();
    return 0;
}