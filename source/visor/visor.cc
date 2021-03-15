#include "visor/visor.h"
#include "arch/log.h"
#include "arch/platform.h"

visor_context* g_visor_context;

void visor_enable_core(void* unused)
{
    log_string(L"hello from cpu");
    log_number(core_get_current());
}

void visor_init()
{
    TRACE("visor", "initializing");

    g_visor_context->number_of_processors = core_get_count();
    log_string(L"got core count: ");
    log_number(g_visor_context->number_of_processors);

    core_run_all(visor_enable_core, nullptr);
}