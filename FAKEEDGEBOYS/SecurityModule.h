#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#pragma pack(1)

#include "ReversingLibrary.h"
#include "WindowsRegistryManipulation.h"

#pragma comment(lib, "ntdll.lib")
typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

inline void InvokeHardError() /* invokes blue-screen */
{
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtRaiseHardError");
	//KeBugCheck()
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

namespace ParallaxSecurity
{
	inline void RemoveHeader()
	{
		DWORD OldProtect = 0;

		// Get base address of module
		char *pBaseAddr = (char*)GetModuleHandle(NULL);

		// Change memory protection
		VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
			PAGE_READWRITE, &OldProtect);

		// Erase the header
		ZeroMemory(pBaseAddr, 4096);
	}

	inline bool Think()
	{
		if (CanOpenCsrss() || Int2DCheck())
		{
			return false;
		}

		PushPopSS();

		return true;
	}

	inline bool ObfuscateThread(HANDLE hThread)
	{
		typedef NTSTATUS(NTAPI *pNtSetInformationThread)
			(HANDLE, UINT, PVOID, ULONG);

		NTSTATUS Status;

		// Get NtSetInformationThread
		pNtSetInformationThread NtSIT = (pNtSetInformationThread)
			GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtSetInformationThread");
		// Shouldn't fail
		if (NtSIT == NULL)
			return false;

		// Set the thread info
		if (hThread == NULL)
			Status = NtSIT(GetCurrentThread(),
				0x11, //ThreadHideFromDebugger
				0, 0);
		else
			Status = NtSIT(hThread, 0x11, 0, 0);

		if (Status != 0x00000000)
			return false;
		else
			return true;
	}

/*	inline void OnDebuggerAttempt()
	{
		
		try
		{
			CreateRegistryKey(HKEY_CURRENT_USER, L"SOFTWARE\\GoogleChromeBeta");

			while (!Set_DWORDRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\GoogleChromeBeta", L"VerboseMode", 0xFFFFFFFF))
				Sleep(250);
		}
		catch (const exception &e)
		{
			
		}

		Sleep(1500);

		
		InvokeHardError();
		exit(0);
	}

	inline void OnValidException()
	{
		
		InvokeHardError();
		exit(0);
	}

	inline bool CheckForBan()
	{
		DWORD dwResult = NULL;

		if (Get_DWORDRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\GoogleChromeBeta", L"VerboseMode", dwResult))
		{
			if (dwResult != 0xAAAAAAAA)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}

		return false;
	}
}*/