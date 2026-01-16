#include <iostream>
#include <unistd.h>     // For fork, getpid, execlp
#include <sys/wait.h>   // For wait
#include <cstdlib>      // For exit

int main() {
    // --- Parent Process Logic ---
    
    // Get the current process ID
    pid_t currentPid = getpid();
    std::cout << "\nProcess ID is: " << currentPid << std::endl;

    // Fork creates a copy of the current process
    pid_t pid = fork();

    if (pid < 0) {
        // --- Error Handling ---
        std::cerr << "Failed to start process (Fork failed)." << std::endl;
        return 1;
    } 
    else if (pid == 0) {
        // --- Child Process Logic ---
        
        // execlp replaces the current process image with "whoami"
        // Parameters: command, arg0 (program name), sentinel (NULL)
        execlp("whoami", "whoami", NULL);
        
        // If execlp returns, it means it failed
        std::cerr << "Failed to execute command." << std::endl;
        exit(1); 
    } 
    else {
        // --- Waiting Logic (Parent) ---
        
        // Wait for the child process to change state (finish)
        wait(NULL);
    }

    return 0;
}