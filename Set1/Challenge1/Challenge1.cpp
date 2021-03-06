// Challenge1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Base64.h"

int main(int argc, const char *argv[])
{
	if (argc < 2) {
		std::cout << "Pass a hex string to encode into base64" << std::endl;
		return 0;
	}

	std::string base64;
	int ret = Base64::Encode(argv[1], base64);

	if (ret == -1) {
		return ret;
	}

	std::cout << base64 << std::endl;

	return 0;
}
