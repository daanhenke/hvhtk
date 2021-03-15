#include "arch/bitmap.h"

void bitmap_init(bitmap* header, uint32_t* buffer, uint32_t size)
{
    header->size = size;
    header->buffer = buffer;
    header->next_available_index = 0;
    header->set_count = 0;
}