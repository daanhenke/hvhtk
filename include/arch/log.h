#pragma once

#include <stdint.h>

#define TRACE(prefix, msg) log_string(L"[" prefix "]: " msg "\r\n")
#define TRACEHEX(prefix, num) log_string(L"" prefix); log_number((uint64_t)num);

void log_string(wchar_t* msg);
void log_char(wchar_t msg);
void log_number(uint64_t number);