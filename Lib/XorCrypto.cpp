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

bool GetAverageHammingDistance(const ByteVector &bytes, size_t keySize, double &avgHammingdistance)
{
	static const size_t MAX_CHUNKS = 2;
	std::vector<ByteVector> chunks;

	for (size_t chunkOffset = 0; (chunkOffset + keySize) < bytes.size(); chunkOffset += keySize) {
		chunks.push_back(ByteVector(bytes.begin() + chunkOffset, bytes.begin() + chunkOffset + keySize));
		if (chunks.size() == MAX_CHUNKS)
			break;
	}

	if (chunks.size() != MAX_CHUNKS) {
		return false;
	}

	std::vector<double> hammingDistances;
	for (size_t i = 1; i < chunks.size(); ++i) {
		uint32_t hammingDistance = Utils::HammingDistance(chunks[i - 1], chunks[i]);
		double normalizedHammingDistance = (double)hammingDistance / keySize;
		hammingDistances.push_back(normalizedHammingDistance);
	}

	avgHammingdistance = 0;

	for (auto hd : hammingDistances) {
		avgHammingdistance += hd;
	}

	avgHammingdistance /= hammingDistances.size();
}

bool MultiByteXorCrypto::BruteForceDecrypt(const std::string & ct, ByteVector & key, std::string & pt)
{
	ByteVector bytes;
	Utils::ConvertHexStringToByteArray(ct, bytes);

	std::map<size_t, double> avgHammingDistancePerKeySize;

	for (size_t keySize = 2; keySize <= 40; ++keySize) {
		avgHammingDistancePerKeySize[keySize] = std::numeric_limits<double>::max();

		double avgHammingDistance = 0;

		if (!GetAverageHammingDistance(bytes, keySize, avgHammingDistance)) {
			continue;
		}

		avgHammingDistancePerKeySize[keySize] = avgHammingDistance;
	}

	// Since maps are by default sorted by key, we need to get first 5 elements from the map and compare them
	size_t elements = 0;

	for (auto iter = avgHammingDistancePerKeySize.begin(); iter != avgHammingDistancePerKeySize.end() && elements < 5; ++iter, ++elements) {
		if ()
	}

	return true;
}
