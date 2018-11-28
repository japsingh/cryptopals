#include "pch.h"
#include "gtest\gtest.h"
#include "Utils.h"
#include "XorCrypto.h"

TEST(XorCryptoTests, EncryptDecrypt)
{
	ByteVector key = { 'I', 'C', 'E' };
	std::vector<std::string> plainText = {
		"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal" 
	};
	std::vector<std::string> cipherText = {
		"0B3637272A2B2E63622C2E69692A23693A2A3C6324202D623D63343C2A26226324272765272A282B2F20430A652E2C652A3124333A653E2B2027630C692B20283165286326302E27282F"
	};

	for (size_t i = 0; i < plainText.size(); ++i) {
		ByteVector pt;
		ByteVector ct;
		Utils::ConvertAsciiStringToByteArray(plainText[i], pt);
		MultiByteXorCrypto::Encrypt(pt, key, ct);

		std::string ctStr;
		Utils::ConvertByteArrayToHexString(ct, ctStr);
		ASSERT_EQ(ctStr, cipherText[i]);
	}
}

TEST(XorCryptoTests, BruteForceDecrypt)
{
	ByteVector key = { 'I', 'C', 'E' };
	std::vector<std::string> plainText = {
		"Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
	};
	std::vector<std::string> cipherText = {
		"0B3637272A2B2E63622C2E69692A23693A2A3C6324202D623D63343C2A26226324272765272A282B2F20430A652E2C652A3124333A653E2B2027630C692B20283165286326302E27282F"
	};

	for (size_t i = 0; i < plainText.size(); ++i) {
		ByteVector key;
		std::string pt;
		MultiByteXorCrypto::BruteForceDecrypt(cipherText[i], key, pt);

		ASSERT_EQ(pt, plainText[i]);
	}
}
