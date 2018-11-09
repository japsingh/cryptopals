#include "stdafx.h"
#include "Base64.h"
#include "Types.h"
#include "Converter.h"

static const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char PAD = '=';

std::string SetOfFour(const byte_t setOf3[3])
{
	char setOf4[5]{};
	setOf4[0] = ALPHABET[(setOf3[0] & 0xFC) >> 2];
	setOf4[1] = ALPHABET[((setOf3[0] & 0x03) << 4) | ((setOf3[1] & 0xF0) >> 4)];
	setOf4[2] = ALPHABET[((setOf3[1] & 0x0F) << 2) | ((setOf3[2] & 0xC0) >> 6)];
	setOf4[3] = ALPHABET[setOf3[2] & 0x3F];

	return setOf4;
}

bool Base64::Encode(const std::string &hexString, std::string &base64)
{
	ByteVector byteArray;
	if (!Converter::ConvertHexStringToByteArray(hexString, byteArray)) {
		return false;
	}

	byte_t setOf3[3]{};
	size_t bytesInBuf = 0;

	for (auto b : byteArray) {
		setOf3[bytesInBuf] = b;
		++bytesInBuf;

		if (bytesInBuf == 3) {
			std::string setOf4 = SetOfFour(setOf3);
			base64 += setOf4;
			bytesInBuf = 0;
			setOf3[0] = setOf3[1] = setOf3[2] = 0;
		}
	}

	// padding of ==
	if (bytesInBuf == 1) {
		std::string setOf4 = SetOfFour(setOf3);
		base64 += setOf4[0];
		base64 += setOf4[1];
		base64 += PAD;
		base64 += PAD;
	}
	// padding of =
	else if (bytesInBuf == 2) {
		std::string setOf4 = SetOfFour(setOf3);
		base64 += setOf4[0];
		base64 += setOf4[1];
		base64 += setOf4[2];
		base64 += PAD;
	}
	return true;
}
