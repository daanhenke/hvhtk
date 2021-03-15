#pragma once

#include "cpu/memory.h"
#include "arch/host.h"

void host_set_gdt(tss* new_tss, segment_descriptor_register new_gdt, uint64_t new_gdt_size, gdtr* original_gdtr);

extern "C" void host_interrupt_handler(void* stack);