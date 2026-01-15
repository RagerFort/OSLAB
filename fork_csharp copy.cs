using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        try
        {
            // --- Parent Process Logic (Equivalent to the 'else' block) ---
            
            // Get the current process ID (getpid)
            int currentPid = Process.GetCurrentProcess().Id;
            Console.WriteLine($"\nProcess ID is: {currentPid}");

            // --- Child Process Logic (Equivalent to the 'pid == 0' block) ---

            // Prepare to run the "whoami" command
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "whoami"; 
            startInfo.UseShellExecute = false; // Execute directly, not via cmd/shell
            
            // Start the child process
            using (Process childProcess = Process.Start(startInfo))
            {
                // --- Waiting Logic (Equivalent to 'wait(NULL)') ---
                if (childProcess != null)
                {
                    childProcess.WaitForExit();
                }
            }
        }
        catch (Exception ex)
        {
            // Equivalent to the 'pid < 0' error check
            Console.WriteLine("Failed to start process.");
            Console.WriteLine(ex.Message);
            Environment.Exit(1);
        }
    }
}