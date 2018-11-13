// Challenge3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "XorCrypto.h"
#include "Utils.h"

int main()
{
	std::string ct("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	for (size_t i = 0; i <= 255; ++i) {
		std::string pt;
		SingleByteXorCrypto::Decrypt(ct, static_cast<byte_t>(i), pt);
		std::string ascii;
		Utils::ConvertHexStringToAsciiString(pt, ascii);
		std::cout << ascii.c_str() << std::endl;
	}
}
