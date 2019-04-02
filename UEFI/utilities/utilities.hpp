#pragma once
#include "../basic_types.h"

inline const CHAR16* operator "" _u(const char16_t* str, size_t)
{
	return (const CHAR16*)(str);
}