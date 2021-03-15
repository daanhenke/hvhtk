#include "arch/host.h"
#include "arch/platform.h"
#include "arch/efi/libefi.h"
#include "arch/log.h"

#include "cpu/asm.h"
#include "cpu/defines.h"
#include "cpu/memory.h"

#define PAGE_SHIFT_2MB      21

typedef struct host_context
{
    pml4e pml4[PML4E_ENTRY_COUNT_64] ALIGN(EFI_PAGE_SIZE);
    pdpte pdpt[1][PDPTE_ENTRY_COUNT_64] ALIGN(EFI_PAGE_SIZE);
    pde pdt[1][PDPTE_ENTRY_COUNT_64][PDE_ENTRY_COUNT_64] ALIGN(EFI_PAGE_SIZE);
    cr3 cr3;
    idt idt[IDT_ENTRY_COUNT];
    idtr idtr;
} host_context;

host_context g_host_context;

void host_init()
{
    TRACE("host", "initializing...");

    TRACE("host", "setting up page tables");
    auto pml4 = g_host_context.pml4;
    auto pdpt = g_host_context.pdpt[0];

    pml4[0].present = 1;
    pml4[0].write = 1;
    pml4[0].page_frame_number = ((uint64_t) pdpt >> EFI_PAGE_SHIFT);

    for (uint32_t pdpt_i = 0; pdpt_i < PDPTE_ENTRY_COUNT_64; pdpt_i++)
    {
        pde* pdt = g_host_context.pdt[0][pdpt_i];

        pdpt[pdpt_i].present = 1;
        pdpt[pdpt_i].write = 1;
        pdpt[pdpt_i].page_frame_number = ((uint64_t) pdt >> EFI_PAGE_SHIFT);

        for (uint32_t pd_i = 0; pd_i < PDE_ENTRY_COUNT_64; pd_i++)
        {
            auto phys = address_from_indexes(0, pdpt_i, pd_i, 0);

            pdt[pd_i].present = 1;
            pdt[pd_i].write = 1;
            pdt[pd_i].large_page = 1;
            pdt[pd_i].page_frame_number = phys >> PAGE_SHIFT_2MB;
        }
    }

    g_host_context.cr3.address_of_page_directory = (uint64_t) pml4 >> EFI_PAGE_SHIFT;

    TRACE("host", "setting up idt");
    uint64_t handler_base = (uint64_t) &interrupt_handlers;
    for (uint32_t i = 0; i < IDT_ENTRY_COUNT; i++)
    {
        uint64_t handler_size = i < 0x80 ? 9 : 11;
        uint64_t handler_addr = handler_base + i * handler_size;

        g_host_context.idt[i].offset_15_0 = (uint16_t) handler_addr;
        g_host_context.idt[i].offset_31_16 = (uint16_t) (handler_addr >> 16);
        g_host_context.idt[i].offset_63_32 = (uint32_t) (handler_addr >> 32);
        g_host_context.idt[i].segment_selector = cpu_getcs();
        g_host_context.idt[i].gate_type = 0x8e;
    }

    g_host_context.idtr.limit = sizeof(g_host_context.idt) - 1;
    g_host_context.idtr.base_address = (uint64_t) (&g_host_context.idt[0]);

    TRACE("host", "done!");
}