#pragma once

#include <stdint.h>

// #define SPIN_LOCK_RELEASED ((uint64_t) 1)
// #define SPIN_LOCK_ACQUIRED ((uint64_t) 2)
// typedef volatile uint64_t spinlock;

#define ALIGN(x) __attribute__((aligned(x)))

#define SPIN_LOCK_CREATE(name) volatile uint64_t name ## SPINLOCK
#define SPIN_LOCK_LOCK(name) while (! __sync_bool_compare_and_swap(& name ## SPINLOCK, 0, 1)); __sync_synchronize();
#define SPIN_LOCK_UNLOCK(name) __sync_synchronize(); name ## SPINLOCK = 0;

void platform_init();

void set_memory(void* address, uint64_t size, uint8_t value);
void zero_memory(void* address, uint64_t size);

void* allocate_pages(uint64_t page_count);
void free_pages(void* address, uint64_t page_count);

typedef void(* core_startup_fn)(void* arg);

uint64_t core_get_count();
uint64_t core_get_current();
void core_run_all(core_startup_fn function, void* arg);