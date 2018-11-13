// Challenge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Utils.h"

int main()
{
	std::string result;
	if (!Utils::XorHexStrings("1c0111001f010100061a024b53535009181c",
		"686974207468652062756c6c277320657965", result)) {
		std::cout << "Failed!" << std::endl;
	}
	else if (result != "746865206B696420646F6E277420706C6179") {
		std::cout << "Failed!" << std::endl;
	}

    std::cout << result.c_str() << std::endl;
}
