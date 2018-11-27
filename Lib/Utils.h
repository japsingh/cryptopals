#pragma once
#include "Types.h"

class Utils
{
public:
	static bool IsEven(size_t n);
	static bool IsNumber(char c);
	static bool IsAlpha(char c);
	static bool IsHexAlpha(char c);
	static bool IsHexDigit(char c);
	static char ToUpper(char c);
	static void ToUpper(std::string &str);

	static byte_t LeftNibble(byte_t b);
	static byte_t RightNibble(byte_t b);

	static byte_t BitAt(byte_t b, byte_t pos);
	static byte_t BitsSet(byte_t b);

	static bool ConvertHexStringToByteArray(const std::string &hex, ByteVector &byteArray);
	static bool ConvertByteArrayToHexString(const ByteVector &byteArray, std::string &hex,
		bool hexAlphabetInCaps = true);
	static bool ConvertHexStringToAsciiString(const std::string &hex, std::string &ascii);
	static bool ConvertByteArrayToAsciiString(const ByteVector &bytes, std::string &ascii,
		bool failIfNonPrintableCharacters = false);
	static void ConvertAsciiStringToByteArray(const std::string &ascii, ByteVector &bytes);
	static bool ConvertAsciiStringToHexString(const std::string &ascii, std::string &hex);

	static byte_t ConvertHexAlphabetToNibble(char hexAlphabet);
	static bool ConvertNibbleToHexAlphabet(byte_t nibble, char &hexAlphabet,
		bool hexAlphabetInCaps = true);


	static bool XorHexStrings(const std::string &lhs, const std::string &rhs, std::string &result,
		bool hexAlphabetInCaps = true);
	static bool XorBytes(const ByteVector &lhs, const ByteVector &rhs, ByteVector &result);
	static void XorWithSingleByte(const ByteVector & pt, byte_t rhs, ByteVector & ct);
	static void XorWithMultiBytes(const ByteVector & pt, const ByteVector &bytes, ByteVector & ct);

	static uint32_t HammingDistance(const std::string &str1, const std::string &str2);
	static uint32_t HammingDistance(const ByteVector &bytes1, const ByteVector &bytes2);
};