#include "stdafx.h"
#include "XorCrypto.h"
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
