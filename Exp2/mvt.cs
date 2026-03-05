using System; // Tell the program to use C#'s built-in tools like Console for input/output

class MemoryMVT { // Create a blueprint called MemoryMVT that holds all variable memory management behavior
    private int totalMemory; // Store the total memory available entered by the user
    private int[] processes = new int[10]; // Create a list to hold up to 10 process memory sizes
    private int numProcesses = 0; // Start the process counter at zero
    private int remaining = 0; // Track how much memory is still available after each allocation

    public void GetInput() { // Define a function that asks the user for the total available memory
        Console.Write("\nEnter the total memory available (in Bytes): "); // Ask the user to type the total memory
        totalMemory = int.Parse(Console.ReadLine()); // Read and convert the input into a number, then save it
        remaining = totalMemory; // Set the remaining memory equal to the total at the start since nothing is allocated yet
    }

    public void Allocate() { // Define a function that dynamically assigns memory to each process one at a time
        char ch = 'y'; // Start with 'y' so the loop runs at least once, simulating the user wanting to continue

        for (int i = 0; ch == 'y'; i++, numProcesses++) { // Keep looping as long as the user wants to add more processes
            Console.Write($"\nEnter memory required for process {i + 1} (in Bytes): "); // Ask how much memory the next process needs
            processes[i] = int.Parse(Console.ReadLine()); // Read and save the process size into the list

            if (processes[i] <= remaining) { // Check if the process fits within the remaining available memory
                Console.WriteLine($"\nMemory is allocated for Process {i + 1}"); // Confirm that the process was successfully given memory
                remaining -= processes[i]; // Subtract the process size from the remaining memory
            } else { // If the process is too large for the remaining memory
                Console.WriteLine("\nMemory is Full"); // Inform the user that there is not enough memory left
                break; // Stop the loop since no more processes can be accommodated
            }

            Console.Write("\nDo you want to continue(y/n): "); // Ask the user if they want to add another process
            ch = char.Parse(Console.ReadLine()); // Read the user's answer and save it — if 'n', the loop will stop
        }
    }

    public void DisplayResults() { // Define a function that prints the final summary of all memory allocations
        Console.WriteLine($"\n\nTotal Memory Available: {totalMemory}"); // Show the original total memory the user entered
        Console.WriteLine("\nPROCESS\t\tMEMORY ALLOCATED"); // Print the table header for the results

        for (int i = 0; i < numProcesses; i++) // Loop through each successfully allocated process
            Console.WriteLine($"\t{i + 1}\t\t{processes[i]}"); // Print each process number and the memory it was given

        Console.WriteLine($"\nTotal Memory Allocated is {totalMemory - remaining}"); // Show how much memory was used in total by subtracting remaining from total
        Console.WriteLine($"Total External Fragmentation is {remaining}"); // Show the leftover memory that was never allocated — this is external fragmentation
    }
}

class Program { // Define the main starting point of the application
    static void Main(string[] args) { // This is the first function that runs when the program starts
        MemoryMVT mem = new MemoryMVT(); // Create a new instance of the MemoryMVT class — like activating the blueprint
        mem.GetInput(); // Call GetInput to ask the user for total memory
        mem.Allocate(); // Call Allocate to dynamically assign memory to each process
        mem.DisplayResults(); // Call DisplayResults to print the final allocation summary
    }
}