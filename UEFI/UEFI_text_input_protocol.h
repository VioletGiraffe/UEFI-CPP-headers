#pragma once
#include "UEFI_types.h"

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID {0x387477c1,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

struct EFI_INPUT_KEY {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
};

// Resets the input device hardware.
typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) (
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
	);

// Reads the next keystroke from the input device.
typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
	OUT EFI_INPUT_KEY *Key
	);

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET Reset;
	EFI_INPUT_READ_KEY ReadKeyStroke;
	EFI_EVENT WaitForKey;
};