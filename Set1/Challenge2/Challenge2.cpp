// Challenge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Utils.h"

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		std::cout << "Pass two hex strings to Xor" << std::endl;
		return 0;
	}

	std::string result;
	bool ret = Utils::XorHexStrings(argv[1], argv[2], result);
	if (!ret) {
		std::cout << "Invalid argument" << std::endl;
	}

    std::cout << result.c_str() << std::endl;
	return 0;
}
