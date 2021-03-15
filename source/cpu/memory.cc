#include "cpu/memory.h"
#include "cpu/asm.h"
#include "arch/log.h"

uint64_t address_from_indexes(uint32_t pml4, uint32_t pdpt, uint32_t pd, uint32_t pt)
{
    virtual_address va;
    
    va.full = 0;
    va.page_map_offset = pml4;
    va.page_directory_pointer_offset = pdpt;
    va.page_directory_offset = pd;
    va.page_table_offset = pt;

    return va.full;
}