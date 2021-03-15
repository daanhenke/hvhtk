#pragma once

#include "cpu/memory.h"

inline cr3 cpu_getcr3()
{
    uint64_t value;
    cr3 result;

    __asm__ __volatile__(
        "mov %%cr3, %%rax\n\t"
        "mov %%rax, %0\n\t"
        : "=m" (value) : : "%rax"
    );

    result.full = value;
    return result;
}

inline gdtr cpu_sgdt()
{
    gdtr result;

    __asm__ __volatile__(
        "sgdt %0\n\t"
        : "=m" (result) : : "%rax"
    );

    return result;
}

inline uint16_t cpu_getcs()
{
    uint16_t result;

    __asm__ __volatile(
        "mov $0, %%rax\n\t"
        "mov %%cs, %%ax\n\t"
        : "=a" (result) : : 
    );

    return result;
}