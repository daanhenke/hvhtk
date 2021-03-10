#pragma once

/*
    Tiny EFI library
*/

#include <stdint.h>

namespace efi
{
    // -- Helper Macros -- //
    #define PROTOCOL_START(name) struct name;
    #define PROTOCOL_METHOD(name, arguments) \
        typedef status (*name)arguments;

    // -- Core Types -- //
    typedef uint8_t boolean;
    typedef uint16_t char16;

    typedef void* event;
    typedef void* handle;

    typedef uint64_t status;
    typedef uint64_t tpl;

    typedef struct guid
    {
        uint32_t d1;
        uint16_t d2;
        uint16_t d3;
        uint8_t d4[8];
    } guid;

    typedef struct table_header
    {
        uint64_t signature;
        uint32_t revision;
        uint32_t header_size;
        uint32_t crc32;
        uint32_t reserved;
    } table_header;

    // -- Protocol definitions -- //
    // TODO: IMPLEMENT
    typedef struct simple_text_input_protocol simple_text_input_protocol;

    // TODO: ADD MISSING METHODS
    PROTOCOL_START(simple_text_input_protocol)
    PROTOCOL_METHOD(text_reset_t, (struct simple_text_output_protocol* _this, boolean extended_verification))
    PROTOCOL_METHOD(text_string_t, (struct simple_text_output_protocol* _this, char16* string))
    typedef struct simple_text_output_protocol
    {
        text_reset_t reset;
        text_string_t output_string;
    } simple_text_output_protocol;

    PROTOCOL_START(boot_services)
    PROTOCOL_METHOD(bs_raise_tpl, (tpl new_tpl))
    PROTOCOL_METHOD(bs_locate_protocol, (guid* protocol, void* registration, void** interface))
    typedef struct boot_services
    {
        bs_raise_tpl raise_tpl;
        bs_raise_tpl fill1;
        bs_raise_tpl fill2;
        bs_raise_tpl fill3;
        bs_raise_tpl fill4;
        bs_raise_tpl fill5;
        bs_raise_tpl fill6;
        bs_raise_tpl fill7;
        bs_raise_tpl fill8;
        bs_raise_tpl fill9;
        bs_raise_tpl fill10;
        bs_raise_tpl fill11;
        bs_raise_tpl fill12;
        bs_raise_tpl fill13;
        bs_raise_tpl fill14;
        bs_raise_tpl fill15;
        bs_raise_tpl fill16;
        bs_raise_tpl fill17;
        bs_raise_tpl fill18;
        bs_raise_tpl fill19;
        bs_raise_tpl fill20;
        bs_raise_tpl fill21;
        bs_raise_tpl fill22;
        bs_raise_tpl fill23;
        bs_raise_tpl fill24;
        bs_raise_tpl fill25;
        bs_raise_tpl fill26;
        bs_raise_tpl fill27;
        bs_raise_tpl fill28;
        bs_raise_tpl fill29;
        bs_raise_tpl fill30;
        bs_raise_tpl fill31;
        bs_raise_tpl fill32;
        bs_raise_tpl fill33;
        bs_raise_tpl fill34;
        bs_raise_tpl fill35;
        bs_raise_tpl fill36;
        bs_locate_protocol locate_protocol;
    } boot_services;

    PROTOCOL_START(runtime_services)
    typedef struct runtime_services
    {
    } runtime_services;

    // -- System Table -- //
    typedef struct system_table
    {
        table_header header;
        char16* firmware_vendor;
        uint32_t firmware_revision;
        handle handle_console_in;
        simple_text_input_protocol* console_in;
        handle handle_console_out;
        simple_text_output_protocol* console_out;
        handle handle_std_err;
        simple_text_output_protocol* std_err;
        runtime_services* runtime_services;
        boot_services* boot_services;
        uint64_t number_of_table_entries;
        void* configuration_table;
    } system_table;
}