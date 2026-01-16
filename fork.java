import java.io.IOException;

public class fork {
    public static void main(String[] args) {
        try {
            // --- Parent Process Logic ---

            // Get the current process ID (Requires Java 9+)
            long currentPid = ProcessHandle.current().pid();
            System.out.println("\nProcess ID is: " + currentPid);

            // --- Child Process Logic ---

            // Prepare to run the "whoami" command
            ProcessBuilder startInfo = new ProcessBuilder("whoami");
            
            // inheritIO ensures the child's output prints to the Parent's console
            // (Similar to how C# behaves by default in some console environments)
            startInfo.inheritIO();

            // Start the child process
            Process childProcess = startInfo.start();

            // --- Waiting Logic ---
            if (childProcess != null) {
                // waitFor() is equivalent to WaitForExit() in C#
                // It throws InterruptedException
                childProcess.waitFor();
            }

        } catch (IOException | InterruptedException ex) {
            // --- Error Handling ---
            System.err.println("Failed to start process.");
            System.err.println(ex.getMessage());
            System.exit(1);
        }
    }
}