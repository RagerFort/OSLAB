//Patrick Alde
using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        try
        {
            int currentPid = Process.GetCurrentProcess().Id;
            Console.WriteLine($"\nProcess ID is: {currentPid}");

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "whoami"; 
            startInfo.UseShellExecute = false; // Execute directly, not via cmd/shell
            

            using (Process childProcess = Process.Start(startInfo))
            {    
                if (childProcess != null)
                {
                    childProcess.WaitForExit();
                }
            }
        }
        catch (Exception ex)
        {
        
            Console.WriteLine("Failed to start process.");
            Console.WriteLine(ex.Message);
            Environment.Exit(1);
        }
    }
}