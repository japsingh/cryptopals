#pragma once
#include "Types.h"

class SingleByteXorCrypto
{
public:
	static bool Encrypt(const std::string &pt, byte_t key, std::string &ct);
	static void Xor(const ByteVector &pt, byte_t key, ByteVector &ct);
	static bool Decrypt(const std::string &ct, byte_t key, std::string &pt);
	static void Decrypt(const ByteVector &ct, byte_t key, ByteVector &pt);
};