// Patrick Alde
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class fork_java {
    private static final Logger LOGGER = Logger.getLogger(fork_java.class.getName());

    public static void main(String[] args) {
        
        long pid = ProcessHandle.current().pid();
        System.out.printf("\nProcess ID is: %d%n", pid);

        try {
            ProcessBuilder builder = new ProcessBuilder("whoami");
            builder.inheritIO(); 
            Process childProcess = builder.start();
            childProcess.waitFor();
            System.exit(0);

        } catch (IOException | InterruptedException e) {
            System.out.println("fork/exec failed");
            LOGGER.log(Level.SEVERE, "An exception occurred", e);
            
            System.exit(1);
        }
    }
}