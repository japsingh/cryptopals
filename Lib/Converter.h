#pragma once
#include "Types.h"
#include <string>
#include <vector>

class Converter
{
public:
	static bool ConvertHexStringToByteArray(const std::string &hex, std::vector<byte_t> &byteArray);
	static byte_t ConvertByteToNibble(byte_t nibble);
};
