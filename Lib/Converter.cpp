#include "stdafx.h"
#include "Converter.h"
#include "Utils.h"
#include <iostream>

bool Converter::ConvertHexStringToByteArray(const std::string & hex, std::vector<byte_t>& byteArray)
{
	if (!Utils::IsEven(hex.length())) {
		std::cout << "Invalid length of input" << std::endl;
		return false;
	}

	for (size_t i = 0; i < hex.length(); ++i) {
		if (!Utils::IsHexDigit(hex[i])) {
			std::cout << "Invalid input" << std::endl;
			return false;
		}

		if (!Utils::IsEven(i)) {
			byte_t c = (ConvertByteToNibble(hex[i - 1]) << 4) | ConvertByteToNibble(hex[i]);
			byteArray.push_back(c);
		}
	}

	return true;
}

byte_t Converter::ConvertByteToNibble(byte_t nibble)
{
	if (nibble >= '0' && nibble <= '9') {
		return nibble - '0';
	}
	if (nibble >= 'A' && nibble <= 'F') {
		return 10 + (nibble - 'A');
	}
	if (nibble >= 'a' && nibble <= 'f') {
		return 10 + (nibble - 'a');
	}

	return 0;
}
