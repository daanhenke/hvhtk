#pragma once

#include <stdint.h>

typedef struct idt
{
    uint16_t offset_15_0;
    uint16_t segment_selector;
    uint8_t reserved1;
    uint8_t gate_type;
    uint16_t offset_31_16;
    uint32_t offset_63_32;
    uint32_t reserved2;
} idt;

#pragma pack(push, 1)
typedef struct tss
{
    uint32_t reserved1;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved2;
    uint64_t ist[7];
    uint64_t reserved3;
    uint16_t reserved4;
    uint16_t io_map_base_address;
} tss;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct segment_descriptor_register
{
    uint16_t limit;
    uint64_t base_address;
} segment_descriptor_register;
#pragma pack(pop)

typedef segment_descriptor_register gdtr, idtr;

typedef struct pml4e
{
    uint64_t present: 1;
    uint64_t write: 1;
    uint64_t supervisor: 1;
    uint64_t page_level_write_through: 1;
    uint64_t page_level_cache_disable: 1;
    uint64_t accessed: 1;
    uint64_t must_be_zero: 1;
    uint64_t ignored1: 4;
    uint64_t page_frame_number: 36;
    uint64_t ignored2: 11;
    uint64_t execute_disable: 1;
} pml4e;

typedef union
{
    uint64_t full;
    struct {
        uint64_t present: 1;
        uint64_t write: 1;
        uint64_t supervisor: 1;
        uint64_t page_level_write_through: 1;
        uint64_t page_level_cache_disable: 1;
        uint64_t accessed: 1;
        uint64_t large_page: 1;
        uint64_t ignored1: 4;
        uint64_t page_frame_number: 36;
        uint64_t reserved2: 4;
        uint64_t ignored2: 11;
        uint64_t execute_disable: 1;
    };
} pdpte;

typedef union
{
    uint64_t full;
    struct {
        uint64_t present: 1;
        uint64_t write: 1;
        uint64_t supervisor: 1;
        uint64_t page_level_write_through: 1;
        uint64_t page_level_cache_disable: 1;
        uint64_t accessed: 1;
        uint64_t reserved1: 1;
        uint64_t large_page: 1;
        uint64_t ignored1: 4;
        uint64_t page_frame_number: 36;
        uint64_t reserved2: 4;
        uint64_t ignored2: 11;
        uint64_t execute_disable: 1;
    };
} pde;

typedef union
{
    uint64_t full;
    struct {
        uint64_t present: 1;
        uint64_t write: 1;
        uint64_t supervisor: 1;
        uint64_t page_level_write_through: 1;
        uint64_t page_level_cache_disable: 1;
        uint64_t accessed: 1;
        uint64_t dirty: 1;
        uint64_t pat: 1;
        uint64_t global: 1;
        uint64_t ignored1: 3;
        uint64_t page_frame_number: 36;
        uint64_t reserved1: 4;
        uint64_t ignored2: 7;
        uint64_t protection_key: 4;
        uint64_t execute_disable: 1;
    };
} pte;

typedef union
{
    uint64_t full;
    struct {
        uint64_t reserved1: 3;
        uint64_t page_level_write_through: 1;
        uint64_t page_level_cache_disable: 1;
        uint64_t reserved2: 7;
        uint64_t address_of_page_directory: 36;
        uint64_t reserved3: 16;
    };
} cr3;

typedef union
{
    uint64_t full;
    struct {
        uint64_t physical_page_offset: 11;
        uint64_t page_table_offset: 8;
        uint64_t page_directory_offset: 8;
        uint64_t page_directory_pointer_offset: 8;
        uint64_t page_map_offset: 8;
        uint64_t sign_extend: 21;
    };
} virtual_address;

uint64_t address_from_indexes(uint32_t pml4, uint32_t pdpt, uint32_t pd, uint32_t pt);