#include "pch.h"
#include "gtest\gtest.h"
#include "Base64.h"

TEST(Base64Tests, EncodeDecode)
{
	std::string base64;
	ASSERT_TRUE(Base64::Encode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", base64));
	ASSERT_EQ(base64, "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");

	base64.clear();
	ASSERT_TRUE(Base64::Encode("61", base64));
	ASSERT_EQ(base64, "YQ==");

	base64.clear();
	ASSERT_TRUE(Base64::Encode("6162", base64));
	ASSERT_EQ(base64, "YWI=");

	base64.clear();
	ASSERT_TRUE(Base64::Encode("61626364656667", base64));
	ASSERT_EQ(base64, "YWJjZGVmZw==");

	base64.clear();
	ASSERT_TRUE(Base64::Encode("6162636465666768", base64));
	ASSERT_EQ(base64, "YWJjZGVmZ2g=");
}
