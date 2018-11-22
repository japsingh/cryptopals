#pragma once
#include "Types.h"

class SingleByteXorCrypto
{
public:
	static bool Encrypt(const std::string &pt, byte_t key, std::string &ct);
	static bool Decrypt(const std::string &ct, byte_t key, std::string &pt);

	static bool BruteForceDecrypt(const std::string &ct, byte_t &key, std::string &pt, double &score);
};

class MultiByteXorCrypto
{
public:
	static void Encrypt(const ByteVector &pt, const ByteVector &key, ByteVector &ct);
	static bool EncryptHexStr(const std::string &ptHexStr, const ByteVector &key, std::string &ctHexStr);
	static void Decrypt(const ByteVector &ct, const ByteVector &key, ByteVector &pt);
	static bool DecryptHexStr(const std::string &ctHexStr, const ByteVector &key, std::string &ptHexStr);
};
