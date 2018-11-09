#pragma once
#include <string>

class Base64
{
public:
	static bool Encode(const std::string &hexString, std::string &base64);
};