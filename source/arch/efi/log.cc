#include "arch/log.h"
#include "arch/efi/libefi.h"
#include "arch/platform.h"

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
    log_string(L"\r\n");
}

void log_number(uint64_t number)
{
    if (number == 0) return log_char('0');

    const wchar_t* chars = L"0123456789ABCDEF";
    wchar_t buff[sizeof(uint64_t) * 2 + 1];
    buff[sizeof(uint64_t) * 2] = L'\0';
    uint64_t index = sizeof(uint64_t) * 2 - 1;

    for (int i = 0; i < sizeof(uint64_t) * 2; i++) buff[i] = '0';

    while (number > 0)
    {
        uint8_t lowest_nibble = number & 0xF;
        buff[index] = chars[lowest_nibble];
        number = number >> 4;
        index--;
    }

    log_string(buff);
    log_string(L"\r\n");
}
