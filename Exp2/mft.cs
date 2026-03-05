using System;

class MemoryMFT {
    private int totalMemory, blockSize, numBlocks, extFrag;
    private int[] processes = new int[10];
    private int numProcesses;

    public void GetInput() {
        Console.Write("Enter the total memory available (in Bytes): ");
        totalMemory = int.Parse(Console.ReadLine());

        Console.Write("Enter the block size (in Bytes): ");
        blockSize = int.Parse(Console.ReadLine());

        numBlocks = totalMemory / blockSize;
        extFrag = totalMemory - numBlocks * blockSize;

        Console.Write("\nEnter the number of processes: ");
        numProcesses = int.Parse(Console.ReadLine());

        for (int i = 0; i < numProcesses; i++) {
            Console.Write($"Enter memory required for process {i + 1} (in Bytes): ");
            processes[i] = int.Parse(Console.ReadLine());
        }
    }

    public void Allocate() {
        int tif = 0, p = 0, i;

        Console.WriteLine($"\nNo. of Blocks available in memory: {numBlocks}");
        Console.WriteLine("\nPROCESS\tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION");

        for (i = 0; i < numProcesses && p < numBlocks; i++) {
            Console.Write($"\n {i + 1}\t\t{processes[i]}");
            if (processes[i] > blockSize)
                Console.Write("\t\tNO\t\t---");
            else {
                Console.Write($"\t\tYES\t\t{blockSize - processes[i]}");
                tif += blockSize - processes[i];
                p++;
            }
        }

        if (i < numProcesses)
            Console.WriteLine("\nMemory is Full, Remaining Processes cannot be accommodated");

        Console.WriteLine($"\n\nTotal Internal Fragmentation is {tif}");
        Console.WriteLine($"Total External Fragmentation is {extFrag}");
    }
}

class Program {
    static void Main(string[] args) {
        MemoryMFT mem = new MemoryMFT();
        mem.GetInput();
        mem.Allocate();
    }
}