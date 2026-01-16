#include <iostream>
#include <unistd.h>     // For fork, getpid, execlp
#include <sys/wait.h>   // For wait
#include <cstdlib>      // For exit

int main() {
    // --- Parent Process Logic ---
    
    // Get the current process ID
    pid_t currentPid = getpid();

    // Fork 3 child processes
    for(int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            // --- Error Handling ---
            std::cerr << "Failed to start process (Fork failed)." << std::endl;
            return 1;
        } 
        else if (pid == 0) {
            // --- Child Process Logic ---
            
            std::cout << i+1 << " Process ID: " << getpid() << std::endl;
            exit(0); 
        }
    }

    // --- Waiting Logic (Parent) ---
    
    // Wait for all 3 child processes to finish
    for(int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}