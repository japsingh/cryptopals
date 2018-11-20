#include "stdafx.h"
#include "XorCrypto.h"
#include "FrequencyAnalysis.h"
#include "Utils.h"

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

void SingleByteXorCrypto::BruteForceDecrypt(const std::string & ct, byte_t & key, std::string & pt)
{
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

		if (leastScore > d) {
			leastScore = d;
			key = static_cast<byte_t>(i);
			pt.clear();
			pt.assign(ascii);
		}
	}
}
