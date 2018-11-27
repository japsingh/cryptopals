#include "pch.h"
#include "gtest\gtest.h"
#include "Utils.h"

TEST(UtilsTests, Xor)
{
	std::string result;
	ASSERT_TRUE(Utils::XorHexStrings("1c0111001f010100061a024b53535009181c",
		"686974207468652062756c6c277320657965", result));
	ASSERT_EQ(result, "746865206B696420646F6E277420706C6179");
}

TEST(HammingDistanceTests, Simple)
{
	ASSERT_EQ(37, Utils::HammingDistance("this is a test", "wokka wokka!!!"));
}