#include "stdafx.h"
#include "Utils.h"

bool Utils::IsEven(size_t n)
{
	return (n % 2) == 0;
}

bool Utils::IsHexDigit(byte_t c)
{
	return ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9'));
}
