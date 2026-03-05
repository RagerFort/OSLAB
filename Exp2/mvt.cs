using System;

class MemoryMVT {
    private int totalMemory;
    private int[] processes = new int[10];
    private int numProcesses = 0;
    private int remaining = 0;

    public void GetInput() {
        Console.Write("\nEnter the total memory available (in Bytes): ");
        totalMemory = int.Parse(Console.ReadLine());
        remaining = totalMemory;
    }

    public void Allocate() {
        char ch = 'y';

        for (int i = 0; ch == 'y'; i++, numProcesses++) {
            Console.Write($"\nEnter memory required for process {i + 1} (in Bytes): ");
            processes[i] = int.Parse(Console.ReadLine());

            if (processes[i] <= remaining) {
                Console.WriteLine($"\nMemory is allocated for Process {i + 1}");
                remaining -= processes[i];
            } else {
                Console.WriteLine("\nMemory is Full");
                break;
            }

            Console.Write("\nDo you want to continue(y/n): ");
            ch = char.Parse(Console.ReadLine());
        }
    }

    public void DisplayResults() {
        Console.WriteLine($"\n\nTotal Memory Available: {totalMemory}");
        Console.WriteLine("\nPROCESS\t\tMEMORY ALLOCATED");

        for (int i = 0; i < numProcesses; i++)
            Console.WriteLine($"\t{i + 1}\t\t{processes[i]}");

        Console.WriteLine($"\nTotal Memory Allocated is {totalMemory - remaining}");
        Console.WriteLine($"Total External Fragmentation is {remaining}");
    }
}

class Program {
    static void Main(string[] args) {
        MemoryMVT mem = new MemoryMVT();
        mem.GetInput();
        mem.Allocate();
        mem.DisplayResults();
    }
}