#include "visor/host.h"
#include "cpu/asm.h"

void host_set_gdt(tss* new_tss, segment_descriptor_register new_gdt, uint64_t new_gdt_size, gdtr* original_gdtr)
{
    gdtr old_gdtr = cpu_sgdt();
}

extern "C" void host_interrupt_handler(void* stack)
{

}