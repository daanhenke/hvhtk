#include "arch/platform.h"
#include "arch/efi/libefi.h"
#include "arch/log.h"

efi::mp_services *mp_services;
efi::guid mp_service_protocol_guid = { 0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08} };

void platform_init()
{
    TRACE("platform", "initializing...");
    
    efi::status status = system_table->boot_services->locate_protocol(&mp_service_protocol_guid, nullptr, (void**) &mp_services);
    if (EFI_ERROR(status))
    {
        TRACE("platform", "couldn't get efi mp services!");
        return;
    }


}

void set_memory(void* address, uint64_t size, uint8_t value)
{
    uint8_t* ptr = (uint8_t*) address;

    while (size > 0)
    {
        *ptr = value;
        ptr++;
        size--;
    }
}

void zero_memory(void* address, uint64_t size)
{
    set_memory(address, size, 0);
}

void* allocate_pages(uint64_t page_count)
{
    void* result;
    
    efi::status status = system_table->boot_services->allocate_pages(efi::allocate_any_pages, efi::runtime_services_data, page_count, (efi::physical_address*) &result);
    if (EFI_ERROR(status))
    {
        return nullptr;
    }

    zero_memory(result, page_count * EFI_PAGE_SIZE);
    return result;
}

void free_pages(void* address, uint64_t page_count)
{
    system_table->boot_services->free_pages((efi::physical_address) address, page_count);
}

uint64_t core_get_count()
{
    uint64_t number_of_processors;
    uint64_t number_of_enabled_processors;

    efi::status status = mp_services->get_number_of_processors(mp_services, &number_of_processors, &number_of_enabled_processors);

    if (EFI_ERROR(status))
    {
        TRACE("platform", "GetNumberOfProcessors failed!");
        return 0;
    }

    return number_of_enabled_processors;
}

uint64_t core_get_current()
{
    uint64_t result;

    efi::status status = mp_services->whoami(mp_services, &result);

    if (EFI_ERROR(status))
    {
        TRACE("platform", "WhoAmI failed!");
        return 0;
    }

    return result;
}

void core_run_all(core_startup_fn function, void* arg)
{
    // Run on current core
    function(arg);

    // Check if there are more cores
    if (core_get_count() == 1)
    {
        return;
    }

    // Execute on those aswell
    efi::status status = mp_services->startup_all_aps(mp_services, (efi::ap_procedure) function, 1, nullptr, 0, arg, nullptr);

    if (EFI_ERROR(status))
    {
        TRACE("platform", "StartupAllAPs failed!");
        return;
    }
}