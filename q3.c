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