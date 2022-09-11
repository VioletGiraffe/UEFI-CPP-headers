#pragma once

#include "basic_types.h"

#ifndef EFIAPI // Forces EFI calling conventions regardless of compiler options 
#ifdef _MSC_VER
#define EFIAPI __cdecl  // Force C calling convention for Microsoft C compiler 
#elif defined(HAVE_USE_MS_ABI)
// Force amd64/ms calling conventions.
#define EFIAPI __attribute__((ms_abi))
#else
#error Unknown compiler. Define EFIAPI so that it forced "cdecl" calling convention.
#endif
#endif

using EFI_HANDLE = void*;
using EFI_EVENT = void*;

enum BOOLEAN : UINT8
{
	FALSE = 0,
	TRUE = 1
};

enum EFI_STATUS : UINTN
{
	EFI_SUCCESS = 0,
	EFI_DEVICE_ERROR = 7
};

// Type modifiers defined in the UEFI standard
#define IN
#define OUT
#define OPTIONAL

struct EFI_TABLE_HEADER {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
private:
	UINT32 Reserved;
};

struct EFI_GUID {
	UINT32  Data1;
	UINT16  Data2;
	UINT16  Data3;
	UINT8   Data4[8];
};

typedef UINTN EFI_TPL; // Task priority level