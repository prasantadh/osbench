// This is free and unencumbered software released into the public domain.
// For more information, see UNLICENSE.

#include "common/time.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static const int NLOOPS = 100000;
static const int NUM_PROCESSES = 100;

int main() {

  pid_t processes[NUM_PROCESSES];
  for (int i = 0; i < NLOOPS; ++i) {
    // Create all the processes.
    const double t0 = get_time();

    for (int i = 0; i < NUM_PROCESSES; ++i) {
      pid_t pid = fork();
      if (pid == 0) {
        exit(0);
      } else if (pid > 0) {
        processes[i] = pid;
      } else {
        fprintf(stderr, "*** Unable to create process no. %d\n", i);
        exit(1);
      }
    }

    // Wait for all child processes to terminate.
    for (int i = 0; i < NUM_PROCESSES; ++i) {
      waitpid(processes[i], (int*)0, 0);
    }

    double dt = get_time() - t0;
    printf("%f us / process\n", (dt / (double) NUM_PROCESSES) * 1000000.0);

  }

  fflush(stdout);
  return 0;
}

