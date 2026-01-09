import java.io.IOException;

public class ProcessLab {
    public static void main(String[] args) {
        
        // 1. Get the Current Process ID (Parent logic)
        // Note: ProcessHandle was introduced in Java 9. 
        // For older Java versions, getting PID requires complex hacks.
        long pid = ProcessHandle.current().pid();
        
        System.out.printf("\nProcess ID is: %d%n", pid);

        try {
            // 2. Prepare the child process (Child logic)
            // This is equivalent to setting up execlp("whoami"...)
            ProcessBuilder builder = new ProcessBuilder("whoami");
            
            // This ensures the child process outputs directly to the console
            // just like the C program does.
            builder.inheritIO(); 

            // 3. Start the process
            Process childProcess = builder.start();

            // 4. Wait for the child to finish (Equivalent to wait(NULL))
            childProcess.waitFor();
            
            System.exit(0);

        } catch (IOException | InterruptedException e) {
            // Equivalent to fork failed logic
            System.out.println("fork/exec failed");
            e.printStackTrace();
            System.exit(1);
        }
    }
}