#include "arch/memory.h"
#include "arch/platform.h"
#include "arch/log.h"
#include "arch/efi/libefi.h"
#include "arch/bitmap.h"

typedef struct memory_context
{
    SPIN_LOCK_CREATE(spinlock);
    uint64_t page_count;
    void* allocated_pages;
    uint32_t last_used_index;
    bitmap bitmap_hdr;
    void* bitmap_data;
    uint8_t* lengthmap;
} memory_context;

memory_context g_memory;

void memory_init()
{
    TRACE("memory", "initializing...");

    uint64_t processor_count = core_get_count();
    uint64_t page_count = processor_count * (512 + 64);
    void* pages = allocate_pages(page_count);
    TRACEHEX("pages: ", pages)

    uint64_t bitmap_page_count = EFI_SIZE_TO_PAGES((page_count / 8) + ((page_count % 8) != 0));
    void* bitmap = allocate_pages(bitmap_page_count);
    
    uint64_t lengthmap_page_count = EFI_SIZE_TO_PAGES((page_count * sizeof(uint8_t)));
    void* lengthmap = allocate_pages(lengthmap_page_count);

    g_memory.page_count = page_count;
    g_memory.allocated_pages = pages;
    g_memory.last_used_index = 0;
    bitmap_init(&g_memory.bitmap_hdr, (uint32_t*) bitmap, page_count);
    g_memory.bitmap_data = bitmap;
    g_memory.lengthmap = (uint8_t*) lengthmap;

    TRACE("memory", "initialized succesfully!");
    TRACEHEX("  context: ", &g_memory);
    TRACEHEX("  page count: ", page_count);
}