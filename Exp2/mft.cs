using System; // Tell the program to use C#'s built-in tools like Console for input/output

class MemoryMFT { // Create a blueprint called MemoryMFT that holds all memory management behavior
    private int totalMemory, blockSize, numBlocks, extFrag; // Declare private storage for total memory, block size, number of blocks, and external fragmentation — private means only this class can use them
    private int[] processes = new int[10]; // Create a list that can hold up to 10 process sizes
    private int numProcesses; // Store how many processes the user will enter

    public void GetInput() { // Define a function called GetInput that collects information from the user
        Console.Write("Enter the total memory available (in Bytes): "); // Ask the user to type the total memory
        totalMemory = int.Parse(Console.ReadLine()); // Read what the user typed and convert it into a number, then save it as totalMemory

        Console.Write("Enter the block size (in Bytes): "); // Ask the user to type the size of each memory block
        blockSize = int.Parse(Console.ReadLine()); // Read and convert the block size input, then save it

        numBlocks = totalMemory / blockSize; // Calculate how many equal blocks fit in the total memory by dividing
        extFrag = totalMemory - numBlocks * blockSize; // Calculate leftover memory that cannot form a complete block — this is external fragmentation

        Console.Write("\nEnter the number of processes: "); // Ask the user how many processes they want to enter
        numProcesses = int.Parse(Console.ReadLine()); // Read and save the number of processes

        for (int i = 0; i < numProcesses; i++) { // Repeat the following steps for each process
            Console.Write($"Enter memory required for process {i + 1} (in Bytes): "); // Ask the user how much memory each process needs
            processes[i] = int.Parse(Console.ReadLine()); // Read and save each process's memory requirement into the list
        }
    }

    public void Allocate() { // Define a function called Allocate that handles assigning memory to each process
        int tif = 0, p = 0, i; // Set up counters: tif tracks total internal fragmentation, p tracks how many blocks have been used

        Console.WriteLine($"\nNo. of Blocks available in memory: {numBlocks}"); // Show the user how many blocks are available
        Console.WriteLine("\nPROCESS\tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION"); // Print the table header

        for (i = 0; i < numProcesses && p < numBlocks; i++) { // Go through each process, but stop if all blocks are already used
            Console.Write($"\n {i + 1}\t\t{processes[i]}"); // Print the process number and how much memory it needs
            if (processes[i] > blockSize) // Check if the process needs more memory than one block can hold
                Console.Write("\t\tNO\t\t---"); // If yes, reject it and print NO — it cannot be allocated
            else { // If the process fits within the block size
                Console.Write($"\t\tYES\t\t{blockSize - processes[i]}"); // Print YES and calculate the wasted space left inside the block
                tif += blockSize - processes[i]; // Add the wasted space to the running total of internal fragmentation
                p++; // Count this block as used
            }
        }

        if (i < numProcesses) // Check if there are still processes left that were not allocated
            Console.WriteLine("\nMemory is Full, Remaining Processes cannot be accommodated"); // Inform the user that memory ran out

        Console.WriteLine($"\n\nTotal Internal Fragmentation is {tif}"); // Show the total wasted space inside allocated blocks
        Console.WriteLine($"Total External Fragmentation is {extFrag}"); // Show the leftover memory that could not form a full block
    }
}

class Program { // Define the main starting point of the application
    static void Main(string[] args) { // This is the first function that runs when the program starts
        MemoryMFT mem = new MemoryMFT(); // Create a new instance of the MemoryMFT class — like activating the blueprint
        mem.GetInput(); // Call GetInput to collect all user data
        mem.Allocate(); // Call Allocate to process and display the memory allocation results
    }
}