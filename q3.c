#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <sys/uio.h>

#include <sys/types.h>

#include <unistd.h>

#include <signal.h>

#include <sys/fcntl.h>

int cpid[5];         // holds the pids of the children
int j;                    // index to cpid 

// function to activate when a signal is caught
int sigCatcher() {  
  signal(SIGINT, sigCatcher);  // re-assign the signal catcher
  printf("PID %d caught one\n", getpid());
  if(j > -1)
    	kill(cpid[j], SIGINT);  // send signal to next child in cpid
} 
int main() {
  int i;
  int zombie;
  int status;
  int pid;
  signal(SIGINT, sigCatcher);    // sets a handler for INT signal

for(i=0; i<5; i++){
    if((pid=fork()) ==  0){      		// create new child
      	printf("PID %d ready\n", getpid());
      	j = i-1;
	pause(); 			// wait for signal
     	exit(0);  			// end process (become a zombie)
    }
    else            			// Only father updates the cpid array.
      	cpid[i] = pid;	  
} 
sleep(2);     			// allow children time to enter pause
kill(cpid[4], SIGINT);     		// send signal to first child
sleep(2);                 			// wait for children to become zombies 
for(i=0; i<5; i++){
    zombie = wait(&status); 		// collect zombies
    printf("%d is dead\n", zombie);
  }
  exit(0);
}
