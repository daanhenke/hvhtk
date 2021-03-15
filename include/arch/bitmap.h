#pragma once

#include "arch/efi/libefi.h"

typedef struct bitmap
{
    uint32_t size;
    uint32_t* buffer;
    uint32_t next_available_index;
    uint32_t set_count;
} bitmap;

void bitmap_init(bitmap* header, uint32_t* buffer, uint32_t size);