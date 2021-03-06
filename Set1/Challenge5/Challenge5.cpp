// Challenge5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Utils.h"
#include "XorCrypto.h"

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cout << "Pass a plain text string and a key to xor with" << std::endl;
		return 0;
	}

	std::string plainText(argv[1]);
	ByteVector pt;
	Utils::ConvertAsciiStringToByteArray(plainText, pt);

	ByteVector key;
	Utils::ConvertAsciiStringToByteArray(argv[2], key);

	ByteVector ct;
	MultiByteXorCrypto::Encrypt(pt, key, ct);

	std::string ctHexStr;
	Utils::ConvertByteArrayToHexString(ct, ctHexStr);
	std::cout << ctHexStr.c_str() << std::endl;
}
