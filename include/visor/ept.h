#pragma once

#include <stdint.h>

typedef struct ept_ptr
{
    uint64_t flags;
} ept_ptr;

typedef struct ept_pml4
{
    uint64_t flags;
} ept_pml4;

typedef struct ept_context
{
    ept_ptr pointer;
    ept_pml4 pml4;
} ept_context;