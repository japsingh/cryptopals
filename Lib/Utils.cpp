#include "stdafx.h"
#include "Utils.h"
#include <iostream>

bool Utils::IsEven(size_t n)
{
	return (n % 2) == 0;
}

bool Utils::IsHexAlpha(char c)
{
	return ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

bool Utils::IsNumber(char c)
{
	return (c >= '0' && c <= '9');
}

bool Utils::IsAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Utils::IsHexDigit(char c)
{
	return (IsHexAlpha(c) || IsNumber(c));
}

char Utils::ToUpper(char c)
{
	return ((c >= 'a' && c <= 'z') ? (c - 32) : c);
}

byte_t Utils::LeftNibble(byte_t b)
{
	return ((b & 0xF0) >> 4);
}

byte_t Utils::RightNibble(byte_t b)
{
	return (b & 0x0F);
}

bool Utils::ConvertHexStringToByteArray(const std::string & hex, ByteVector& byteArray)
{
	if (!Utils::IsEven(hex.length())) {
		std::cout << "Invalid length of input" << std::endl;
		return false;
	}

	for (size_t i = 0; i < hex.length(); ++i) {
		if (!Utils::IsHexDigit(hex[i])) {
			std::cout << "Invalid input" << std::endl;
			return false;
		}

		if (!Utils::IsEven(i)) {
			byte_t c = (ConvertHexAlphabetToNibble(hex[i - 1]) << 4) | ConvertHexAlphabetToNibble(hex[i]);
			byteArray.push_back(c);
		}
	}

	return true;
}

byte_t Utils::ConvertHexAlphabetToNibble(char hexAlphabet)
{
	if (hexAlphabet >= '0' && hexAlphabet <= '9') {
		return hexAlphabet - '0';
	}
	if (hexAlphabet >= 'A' && hexAlphabet <= 'F') {
		return 10 + (hexAlphabet - 'A');
	}
	if (hexAlphabet >= 'a' && hexAlphabet <= 'f') {
		return 10 + (hexAlphabet - 'a');
	}

	return 0;
}

bool Utils::ConvertByteArrayToHexString(const ByteVector & byteArray, std::string & hex,
	bool hexAlphabetInCaps)
{
	hex.clear();

	for (auto b : byteArray) {
		char c{};
		if (!ConvertNibbleToHexAlphabet(LeftNibble(b), c, hexAlphabetInCaps)) {
			return false;
		}
		hex += c;

		c = 0;
		if (!ConvertNibbleToHexAlphabet(RightNibble(b), c, hexAlphabetInCaps)) {
			return false;
		}
		hex += c;
	}

	return true;
}

bool Utils::ConvertHexStringToAsciiString(const std::string & hex, std::string & ascii)
{
	ByteVector bytes;
	if (!ConvertHexStringToByteArray(hex, bytes)) {
		return false;
	}

	return ConvertByteArrayToAsciiString(bytes, ascii);
}

bool Utils::ConvertByteArrayToAsciiString(const ByteVector & bytes, std::string & ascii,
	bool /*failIfNonPrintableCharacters*/)
{
	for (auto b : bytes) {
		ascii.push_back((char)b);
	}

	return true;
}

void Utils::ConvertAsciiStringToByteArray(const std::string &ascii, ByteVector &bytes)
{
	bytes.clear();
	for (auto c : ascii) {
		bytes.push_back(c);
	}
}

bool Utils::ConvertAsciiStringToHexString(const std::string &ascii, std::string &hex)
{
	ByteVector bytes;
	ConvertAsciiStringToByteArray(ascii, bytes);
	return ConvertByteArrayToHexString(bytes, hex);
}

bool Utils::ConvertNibbleToHexAlphabet(byte_t nibble, char &hexAlphabet,
	bool hexAlphabetInCaps)
{
	static byte_t HEX_ALPHABET_CAPS[] = { "0123456789ABCDEF" };
	static byte_t HEX_ALPHABET_SMALL[] = { "0123456789abcdef" };

	if (nibble >= 16) {
		return false;
	}

	if (hexAlphabetInCaps) {
		hexAlphabet = HEX_ALPHABET_CAPS[nibble];
	}
	else {
		hexAlphabet = HEX_ALPHABET_SMALL[nibble];
	}

	return true;
}

bool Utils::XorHexStrings(const std::string & lhs, const std::string & rhs, std::string &result,
	bool hexAlphabetInCaps)
{
	if (lhs.length() != rhs.length()) {
		return false;
	}

	if (lhs.empty()) {
		return false;
	}

	ByteVector lhsBytes;
	ByteVector rhsBytes;
	ByteVector resultBytes;

	if (!ConvertHexStringToByteArray(lhs, lhsBytes)) {
		return false;
	}

	if (!ConvertHexStringToByteArray(rhs, rhsBytes)) {
		return false;
	}

	if (!XorBytes(lhsBytes, rhsBytes, resultBytes)) {
		return false;
	}

	return ConvertByteArrayToHexString(resultBytes, result, hexAlphabetInCaps);
}

bool Utils::XorBytes(const ByteVector & lhs, const ByteVector & rhs, ByteVector &result)
{
	if (lhs.size() != rhs.size()) {
		return false;
	}

	if (lhs.empty()) {
		return false;
	}

	result.clear();

	for (size_t i = 0; i < lhs.size(); ++i) {
		result.push_back(lhs[i] ^ rhs[i]);
	}

	return true;
}

void Utils::XorWithSingleByte(const ByteVector & pt, byte_t rhs, ByteVector & ct)
{
	ct.clear();

	for (auto b : pt) {
		ct.push_back(b ^ rhs);
	}
}
