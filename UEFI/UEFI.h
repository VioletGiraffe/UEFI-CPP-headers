#pragma once

#include "UEFI_types.h"
#include "UEFI_text_input_protocol.h"
#include "EFI_boot_services.h"
#include "EFI_scan_codes.h"
#include "EFI_graphics_output_protcol.h"

#include "utilities/utilities.hpp"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID {0x387477c2,0x69c7,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
	);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN const CHAR16 *String // I added `const` so passing string literals and const strings directly is possible. This shouldn't break binary compatibility.
	);

// Verifies that all characters in a string can be output to the target device.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_TEST_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN const CHAR16 *String // I added `const` so passing string literals and const strings directly is possible. This shouldn't break binary compatibility.
	);

// Returns information for an available text mode that the output device(s) supports.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN ModeNumber,
	OUT UINTN *Columns,
	OUT UINTN *Rows
	);

// Sets the output device(s) to a specified mode.
typedef
EFI_STATUS
(*EFIAPI EFI_TEXT_SET_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN ModeNumber
	);

// Sets the background and foreground colors for theOutputString() and ClearScreen() functions.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN Attribute
	);

// Clears the output device(s) display to the currently selected background color.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
	);

// Sets the current coordinates of the cursor position.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN Column,
	IN UINTN Row
	);

// Makes the cursor visible or invisible.
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN Visible
	);

//*******************************************************
// SIMPLE_TEXT_OUTPUT_MODE
//*******************************************************
struct SIMPLE_TEXT_OUTPUT_MODE {
	INT32 MaxMode;
	// current settings
	INT32 Mode;
	INT32 Attribute;
	INT32 CursorColumn;
	INT32 CursorRow;
	BOOLEAN CursorVisible;
};

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET                  Reset;

	EFI_TEXT_STRING          OutputString;
	EFI_TEXT_TEST_STRING            TestString;

	EFI_TEXT_QUERY_MODE             QueryMode;
	EFI_TEXT_SET_MODE               SetMode;
	EFI_TEXT_SET_ATTRIBUTE          SetAttribute;

	EFI_TEXT_CLEAR_SCREEN           ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION    SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR          EnableCursor;

	// Current mode
	SIMPLE_TEXT_OUTPUT_MODE         *Mode;
};

struct EFI_SYSTEM_TABLE {
	EFI_TABLE_HEADER                Hdr;

	CHAR16* FirmwareVendor;
	UINT32  FirmwareRevision;

	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;

	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*ConOut;

	EFI_HANDLE StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;

	struct EFI_RUNTIME_SERVICES* RuntimeServices;
	struct EFI_BOOT_SERVICES*    BootServices;

	UINTN NumberOfTableEntries;
	struct EFI_CONFIGURATION_TABLE *ConfigurationTable;

};
