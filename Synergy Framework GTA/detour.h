#pragma once
#pragma once
#pragma once
#include "stdafx.h"

extern uint8_t hook_stub_section[0x10000] __attribute__((section(".text")));
extern uint32_t stubCount_;

#ifndef DETOUR_H
#define DETOUR_H

uint32_t sys_hen_read_process_memory(uint64_t address, void* data, size_t size);
uint32_t sys_hen_write_process_memory(uint64_t address, void* data, size_t size);
uint32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size);
uint32_t sys_dbg_write_process_memory(uint64_t address, void* data, size_t size);
uint32_t read_memory(uint64_t address, void* data, size_t size);
uint32_t write_memory(uint64_t address, void* data, size_t size);

class Detour {
public:
    template<class T>
    Detour(uint32_t targetAddress, T(*hookFunction), bool jump = false)
    {
        this->m_targetAddress = targetAddress;

        read_memory(targetAddress, this->originalInstructions_, sizeof(this->originalInstructions_));
        uint32_t stubAddress;

        uint32_t hookFunctionStart = *reinterpret_cast<uint32_t*>(hookFunction);


        if (!jump)
        {
            stubAddress = this->allocateStub();


            write_memory(stubAddress, this->originalInstructions_, sizeof(this->originalInstructions_));

            uint32_t continuationAddress = targetAddress + sizeof(this->originalInstructions_);

            uint32_t stubJump[4] = {
                0x3D600000 | (static_cast<uint32_t>((continuationAddress >> 16) & 0xFFFF)),
                0x616B0000 | (static_cast<uint32_t>(continuationAddress & 0xFFFF)),
                0x7D6903A6,
                0x4E800420
            };
            write_memory(stubAddress + sizeof(this->originalInstructions_), stubJump, sizeof(stubJump));
        }


        uint32_t hookJump[4] = {
            0x3D600000 | (static_cast<uint32_t>((hookFunctionStart >> 16) & 0xFFFF)),
            0x616B0000 | (static_cast<uint32_t>(hookFunctionStart & 0xFFFF)),
            0x7D6903A6,
            0x4E800420
        };
        write_memory(targetAddress, hookJump, sizeof(hookJump));

        if (!jump)
        {
            auto* stubAddressPtr = reinterpret_cast<uint32_t*>(stubAddress);
            functionOpd_[0] = reinterpret_cast<uint32_t>(stubAddressPtr);

            uint32_t* tocEntry = *reinterpret_cast<uint32_t**>(0x1001C);
            functionOpd_[1] = tocEntry[1];
        }
    }


    template<typename T = void, typename... Params>
    T CallOriginal(Params... parameters)
    {
        if (functionOpd_[0] == 0) {
     
            return T(); // Retorna um valor padrão
        }
        T(*originalFunction)(Params...) = reinterpret_cast<T(*)(Params...)>(functionOpd_);
        return originalFunction(parameters...);
    }

    ~Detour()
    {
        // Restaura as instruções originais no endereço alvo, se houverem sido salvas
        write_memory(this->m_targetAddress, this->originalInstructions_, sizeof(this->originalInstructions_));
    }

private:
    uint32_t originalInstructions_[4];
    uint32_t functionOpd_[2];
    uint32_t m_targetAddress;

    uint32_t allocateStub()
    {
        uint8_t* stubSection = hook_stub_section;
        uint32_t allocatedStubAddress = reinterpret_cast<uint32_t>(&stubSection[stubCount_ * 0xA0]);
        stubCount_++;
        return allocatedStubAddress;
    }
};

#endif // DETOUR_H
