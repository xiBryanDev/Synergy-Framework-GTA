#include "Detour.h"

bool use_hen_syscalls = false;
uint32_t stubCount_;
uint8_t hook_stub_section[0x10000] __attribute__((section(".text")));


uint32_t sys_hen_read_process_memory(uint64_t address, void* data, size_t size)
{
    system_call_6(8, 0x7777, 0x31, static_cast<uint64_t>(sys_process_getpid()), address, reinterpret_cast<uint64_t>(data), size);
    return_to_user_prog(uint32_t);
}

uint32_t sys_hen_write_process_memory(uint64_t address, void* data, size_t size)
{
    system_call_6(8, 0x7777, 0x32, static_cast<uint64_t>(sys_process_getpid()), address, reinterpret_cast<uint64_t>(data), size);
    return_to_user_prog(uint32_t);
}

uint32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
{
    system_call_4(904, static_cast<uint64_t>(sys_process_getpid()), address, size, reinterpret_cast<uint64_t>(data));
    return_to_user_prog(uint32_t);
}

uint32_t sys_dbg_write_process_memory(uint64_t address, void* data, size_t size)
{
    system_call_4(905, static_cast<uint64_t>(sys_process_getpid()), address, size, reinterpret_cast<uint64_t>(data));
    return_to_user_prog(uint32_t);
}

uint32_t read_memory(uint64_t address, void* data, size_t size)
{
    if (!use_hen_syscalls)
    {
        uint32_t read = sys_dbg_read_process_memory(address, data, size);
        if (read == SUCCEEDED)
        {
            return read;
        }
    }

    use_hen_syscalls = true;
    return sys_hen_read_process_memory(address, data, size);
}

uint32_t write_memory(uint64_t address, void* data, size_t size)
{
    if (!use_hen_syscalls)
    {
        uint32_t write = sys_dbg_write_process_memory(address, data, size);
        if (write == SUCCEEDED)
        {
            return write;
        }
    }

    use_hen_syscalls = true;
    return sys_hen_write_process_memory(address, data, size);
}
