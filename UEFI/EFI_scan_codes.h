#pragma once
#include "basic_types.h"

enum EFI_Scan_Code : UINT16
{
	Cursor_Up = 0x01,
	Cursor_Down = 0x02,
	Cursor_Right = 0x03,
	Cursor_Left = 0x04,
	Function12 = 0x16
};