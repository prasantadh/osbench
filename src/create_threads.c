// This is free and unencumbered software released into the public domain.
// For more information, see UNLICENSE.

#include "common/time.h"

#include <stdio.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <process.h>
#include <windows.h>
#else
#include <pthread.h>
#endif

#if defined(_WIN32)

// WIN32 thread implementation.
typedef HANDLE thread_t;

static unsigned WINAPI thread_fun(void* arg) {
  // We do nothing here...
  (void)arg;
  return 0u;
}

static thread_t create_thread() {
  return (HANDLE)_beginthreadex((void*)0, 0, thread_fun, (void*)0, 0, (unsigned*)0);
}

static void join_thread(thread_t thread) {
  if (WaitForSingleObject(thread, INFINITE) != WAIT_FAILED) {
    CloseHandle(thread);
  }
}

#else

// POSIX thread implementation.
typedef pthread_t thread_t;

static void* thread_fun(void* arg) {
  // We do nothing here...
  (void)arg;
  return (void*)0;
}

static thread_t create_thread() {
  thread_t result;
  pthread_create(&result, (const pthread_attr_t*)0, thread_fun, (void*)0);
  return result;
}

static void join_thread(thread_t thread) {
  pthread_join(thread, (void**)0);
}

#endif  // WIN32

#define NUM_THREADS 100

// static const double BENCHMARK_TIME = 1200.0;

int main() {

  for (int i = 0; i < 100000; ++i) {
    thread_t threads[NUM_THREADS];

    // Create all the child threads.
    for (int i = 0; i < NUM_THREADS; ++i) {
      threads[i] = create_thread();
    }

    // Wait for all the child threads to finish.
    for (int i = 0; i < NUM_THREADS; ++i) {
      join_thread(threads[i]);
    }

  }

  return 0;
}

