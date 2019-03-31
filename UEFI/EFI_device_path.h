#pragma once
#include "UEFI_types.h"

struct EFI_DEVICE_PATH {
	UINT8 Type;
	UINT8 SubType;
	UINT8 Length[2];
};