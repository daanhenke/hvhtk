#include "arch/efi/libefi.h"

efi::system_table* system_table;
efi::guid mp_service_protocol_guid = { 0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08} };

void log_string(efi::char16* msg)
{
    system_table->console_out->output_string(system_table->console_out, msg);
}

void log_string(wchar_t* msg)
{
    log_string((efi::char16*)(msg));
}

void log_char(wchar_t msg)
{
    wchar_t buff[2];
    buff[0] = msg;
    buff[1] = L'\0';
    log_string(buff);
}

void log_number(uint64_t number)
{
    if (number == 0) return log_char('0');

    const wchar_t* chars = L"0123456789ABCDEF";
    wchar_t buff[sizeof(uint64_t) * 2 + 1];
    buff[sizeof(uint64_t) * 2] = L'\0';
    uint64_t index = sizeof(uint64_t) * 2 - 1;

    while (number > 0)
    {
        uint8_t lowest_nibble = number & 0xF;
        buff[index] = chars[lowest_nibble];
        number = number >> 4;
        index--;
    }

    log_string(buff + index + 1);
}

efi::status efi_main(efi::handle module, efi::system_table* st)
{
    system_table = st;
    
    void* meme = 0;
    efi::status status = st->boot_services->locate_protocol(&mp_service_protocol_guid, nullptr, &meme);

    log_string(L"fakka strijder\r\n");
    log_string(L"een Q: ");
    log_char(L'Q');
    log_string(L"\r\n");
    log_number((uint64_t) meme);
    log_number((uint64_t) status);
    log_string(L"\r\n");

    return 0;
}