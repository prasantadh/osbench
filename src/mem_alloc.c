// This is free and unencumbered software released into the public domain.
// For more information, see UNLICENSE.

#include "common/time.h"

#include <stdio.h>
#include <stdlib.h>

#define NUM_ALLOCS 1000000

static void* s_addresses[NUM_ALLOCS];

int main(int argc, const char** argv) {
  (void)argc;
  (void)argv;

  for (int i = 0; i < 5000; ++i) {

    for (int i = 0; i < NUM_ALLOCS; ++i) {
      const size_t memory_size = ((i % 32) + 1) * 4;
      s_addresses[i] = malloc(memory_size);
      ((char*)s_addresses[i])[0] = 1;
    }

    for (int i = 0; i < NUM_ALLOCS; ++i) {
      free(s_addresses[i]);
    }

  }

  return 0;
}

