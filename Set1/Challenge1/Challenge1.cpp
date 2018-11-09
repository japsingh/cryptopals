// Challenge1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Base64.h"

void Test()
{
	std::string base64;
	bool ret = Base64::Encode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", base64);
	if (ret == false || base64 != "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t") {
		std::cout << "Failed!" << std::endl;
	}
	base64.clear();
	ret = Base64::Encode("61", base64);
	if (ret == false || base64 != "YQ==") {
		std::cout << "Failed!" << std::endl;
	}
	base64.clear();
	ret = Base64::Encode("6162", base64);
	if (ret == false || base64 != "YWI=") {
		std::cout << "Failed!" << std::endl;
	}
	base64.clear();
	ret = Base64::Encode("61626364656667", base64);
	if (ret == false || base64 != "YWJjZGVmZw==") {
		std::cout << "Failed!" << std::endl;
	}
	base64.clear();
	ret = Base64::Encode("6162636465666768", base64);
	if (ret == false || base64 != "YWJjZGVmZ2g=") {
		std::cout << "Failed!" << std::endl;
	}
}

int main(int argc, const char *argv[])
{
	if (argc < 2) {
		Test();
//		std::cout << "Pass a hex string to encode into base64" << std::endl;
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
