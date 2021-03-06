// Challenge3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "XorCrypto.h"
#include "Utils.h"
#include "FrequencyAnalysis.h"
#include <algorithm>

int main()
{
	std::string ct("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
	byte_t key = 0;
	std::string pt;
	double score{};
	SingleByteXorCrypto::BruteForceDecrypt(ct, key, pt, score);

	std::cout << "Key : " << key << ", Plain text : " << pt.c_str() << std::endl ;
}
