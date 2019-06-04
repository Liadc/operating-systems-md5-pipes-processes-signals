#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <sys/uio.h>

#include <sys/types.h>

#include <unistd.h>

#include <signal.h>

#include <sys/fcntl.h>

int cpid[5];// holds the pids of the children
int j;// index to cpid 

// function to activate when a signal is caught
int sigCatcher() {
  // re-assign the signal catcher
  signal(SIGINT, sigCatcher);
  printf("PID %d caught one\n", getpid());
  if (j > -1)
    // send signal to next child in cpid
    kill(cpid[j], SIGINT);
}
int main() {
  int i, zombie, status, pid;

  // sets a handler for INT signal
  signal(SIGINT, sigCatcher);

  for (i = 0; i < 5; i++) {
    if ((pid = fork()) == 0) { // create new child
      printf("PID %d ready\n", getpid());
      j = i - 1;
      pause();  // wait for signal
      exit(0);  // end process (become a zombie)
    } else
      // Only father updates the cpid array.
      cpid[i] = pid;
  }
  // allow children time to enter pause
  sleep(2);
  // send signal to first child
  kill(cpid[4], SIGINT);
  for (i = 0; i < 5; i++) {
    zombie = wait(&status);// collect zombies
    printf("%d is dead\n", zombie);
  }
  exit(0);
}
