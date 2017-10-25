/*MIT License

Copyright (c) namazso 2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "sigscan.h"
#include <iostream>
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

SigScan::SigScan(void* base_addr, size_t base_len) : base_addr((char*)base_addr), base_len(base_len)
{
}
SigScan::SigScan(void *insider_addr)
{
	if (!insider_addr)
		return;

	MEMORY_BASIC_INFORMATION mem;

	if (!VirtualQuery(insider_addr, &mem, sizeof(mem)))
		return;

	base_addr = (char*)mem.AllocationBase;

	IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER *)mem.AllocationBase;
	IMAGE_NT_HEADERS *pe = (IMAGE_NT_HEADERS *)((unsigned long)dos + (unsigned long)dos->e_lfanew);

	if (pe->Signature != IMAGE_NT_SIGNATURE) {
		base_addr = nullptr;
		return;
	}

	base_len = (size_t)pe->OptionalHeader.SizeOfImage;
}

SigScan::SigScan(const char* module_name)
{
	HMODULE module = GetModuleHandle(module_name);

	if (module)
	{
		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));

		base_addr = (char *)info.lpBaseOfDll;
		base_len = (size_t)info.SizeOfImage;
	}
}

DWORD SigScan::Scan(const char *signature, int offset)
{
	if (!IsValid())
		return 0;

	int loc = 0;

	for (char *ptr = base_addr; ptr < base_addr + base_len; ptr++)
	{
		if (signature[loc] == '?' || signature[loc] == *ptr)
		{
			if (signature[loc + 1] == '\0')
				return (DWORD)(ptr - loc + offset);

			loc++;
		}
		else {
			loc = 0;
		}
	}

	printf("%s sig failed!\n", signature);
	return 0;

}

DWORD SigScan::CalcAbsAddress(DWORD address)
{
	return DWORD(address + *(signed long*)((DWORD)address) + 4);
}

bool SigScan::IsValid()
{
	return (base_addr && base_len);
}

char *SigScan::GetBase()
{
	return base_addr;
}

size_t SigScan::GetLength()
{
	return base_len;
}