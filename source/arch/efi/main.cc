#include "arch/efi/libefi.h"
#include "arch/log.h"
#include "arch/platform.h"
#include "visor/visor.h"
#include "arch/memory.h"
#include "arch/host.h"

#include "cpu/asm.h"

efi::system_table* system_table;

efi::status efi_main(efi::handle module, efi::system_table* st)
{
    system_table = st;
    
    //void* meme = 0;
    //efi::status status = st->boot_services->locate_protocol(&mp_service_protocol_guid, nullptr, &meme);

    platform_init();
    memory_init();
    host_init();
    visor_init();

    return 0;
}