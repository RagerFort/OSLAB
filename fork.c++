#include <iostream>     // For input-output operations
#include <unistd.h>     // For fork, getpid, execlp
#include <sys/wait.h>   // For wait
#include <cstdlib>      // For exit

int main() {
 

    // Fork 2 child processes
    for(int i = 0; i < 2; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            // --- Error Handling ---
            std::cerr << "Failed to start process (Fork failed)." << std::endl;
            return 1;
        } 
        else if (pid == 0) {
            // --- Child Process Logic ---
            
            std::cout << i+1 << " Process ID: " << getpid() << std::endl;
            exit(0);  // Child process exits after printing its ID
        }
    }

    // --- Waiting Logic (Parent) ---
    
    // Wait for 1 child process to finish
    for(int i = 0; i < 1; i++) {
          wait(NULL);
         pid_t currentPid = getpid();
          std::cout << "Parent Process ID is: " << currentPid << std::endl;
        
    }



    return 0;
}