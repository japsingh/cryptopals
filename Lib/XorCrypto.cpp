#include "stdafx.h"
#include "XorCrypto.h"
#include "FrequencyAnalysis.h"
#include "Utils.h"
#include <iostream>

bool SingleByteXorCrypto::Encrypt(const std::string & ptHexStr, byte_t key, std::string &ctHexStr)
{
	ByteVector pt;
	ByteVector ct;

	if (!Utils::ConvertHexStringToByteArray(ptHexStr, pt)) {
		return false;
	}

	Utils::XorWithSingleByte(pt, key, ct);

	return Utils::ConvertByteArrayToHexString(ct, ctHexStr);
}

// Decryption is exactly same as encryption
bool SingleByteXorCrypto::Decrypt(const std::string & ct, byte_t key, std::string & pt)
{
	return Encrypt(ct, key, pt);
}

bool SingleByteXorCrypto::BruteForceDecrypt(const std::string & ct, byte_t & key, std::string & pt, double &score)
{
	bool ret = false;
	double leastScore = std::numeric_limits<double>::max();
	for (int i = 0; i <= 255; ++i) {
		std::string potential_pt;
		SingleByteXorCrypto::Decrypt(ct, static_cast<byte_t>(i), potential_pt);
		std::string ascii;
		Utils::ConvertHexStringToAsciiString(potential_pt, ascii);
		double d = FrequencyAnalysis::GetEnglishStringFrequencyScore(ascii);
		if (isnan(d)) {
			continue;
		}
		//std::cout << ascii.c_str() << std::endl;

		if (leastScore > d) {
			leastScore = d;
			key = static_cast<byte_t>(i);
			pt.clear();
			pt.assign(ascii);
			ret = true;
		}
	}

	score = leastScore;
	return ret;
}

bool MultiByteXorCrypto::EncryptHexStr(const std::string & ptHexStr, const ByteVector &key,
	std::string &ctHexStr)
{
	ByteVector pt;
	ByteVector ct;

	if (!Utils::ConvertHexStringToByteArray(ptHexStr, pt)) {
		return false;
	}

	Utils::XorWithMultiBytes(pt, key, ct);

	return Utils::ConvertByteArrayToHexString(ct, ctHexStr);
}

// Decryption is exactly same as encryption
bool MultiByteXorCrypto::DecryptHexStr(const std::string & ctHexStr, const ByteVector &key, std::string & ptHexStr)
{
	return EncryptHexStr(ctHexStr, key, ptHexStr);
}

void MultiByteXorCrypto::Encrypt(const ByteVector & pt, const ByteVector &key, ByteVector &ct)
{
	Utils::XorWithMultiBytes(pt, key, ct);
}

// Decryption is exactly same as encryption
void MultiByteXorCrypto::Decrypt(const ByteVector & ct, const ByteVector &key, ByteVector & pt)
{
	return Encrypt(ct, key, pt);
}
