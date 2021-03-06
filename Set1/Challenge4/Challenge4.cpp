// Challenge4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "XorCrypto.h"

int main(int argc, char *argv[])
{
	double leastScore = std::numeric_limits<double>::max();
	std::string finalPT;
	byte_t finalKey{};

	std::fstream fin;
	if (argc >= 2) {
		fin.open(argv[1], std::ios::in);
	}
	else {
		fin.open("..\\..\\Input\\4.txt", std::ios::in);
	}

	while (!fin.eof()) {
		char buf[1024]{};
		fin.getline(buf, _countof(buf));
		byte_t key{};
		std::string pt;
		double score{};
		if (!SingleByteXorCrypto::BruteForceDecrypt(buf, key, pt, score)) {
			continue;
		}
		if (leastScore > score) {
			leastScore = score;
			finalPT = pt;
			finalKey = key;
		}
	}
	std::cout << "Key: " << finalKey << ", Plaintext: " << finalPT.c_str() << std::endl;
}
