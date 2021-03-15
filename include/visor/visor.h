#pragma once

#include "visor/ept.h"
#include "cpu/memory.h"

typedef struct processor_context
{
    ept_context ept_context;
    segment_descriptor_register host_gdt[16];
    segment_descriptor_register tss;
} processor_context;

typedef struct visor_context
{
    uint64_t number_of_processors;
    processor_context* processor_context;
} visor_context;

extern visor_context* g_visor_context;

void visor_init();