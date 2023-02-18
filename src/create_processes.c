// This is free and unencumbered software released into the public domain.
// For more information, see UNLICENSE.

#include "common/time.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static const int NUM_PROCESSES = 100;

int main() {
  printf("Benchmark: Create/teardown of %d processes...\n", NUM_PROCESSES);
  fflush(stdout);

  pid_t processes[NUM_PROCESSES];
  for (int i = 0; i < 40000; ++i) {
    // Create all the processes.
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

  }

  return 0;
}

