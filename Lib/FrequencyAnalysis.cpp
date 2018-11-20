#include "stdafx.h"
#include "FrequencyAnalysis.h"
#include "Utils.h"
#include <math.h>

std::map<char, double> ENGLISH_FREQ = {
	{ 'E', 0.1202 }, { 'T', 0.091 }, { 'A', 0.0812 }, { 'O', 0.0768 },
	{ 'I', 0.0731 }, { 'N', 0.0695 }, { 'S', 0.0628 }, { 'H', 0.0592 },
	{ 'R', 0.0602 }, { 'L', 0.0398 },  { 'D', 0.0432 }, { 'C', 0.0271 },
	{ 'U', 0.0288 }, { 'M', 0.0261 }, { 'W', 0.0209 }, { 'F', 0.023 },
	{ 'G', 0.0203 }, { 'Y', 0.0211 },  { 'P', 0.0182 }, { 'B', 0.0149 },
	{ 'V', 0.0111 }, { 'K', 0.0069 }, { 'J', 0.001 }, { 'X', 0.0017 },
	{ 'Q', 0.0011 }, { 'Z', 0.0007 }, { ' ', 0.171662 }
};

void FrequencyAnalysis::ByteFrequencyAnalysis(const ByteVector & bytes, ByteFrequencyMap & result)
{
	result.clear();

	for (auto b : bytes) {
		result[b].count++;
		result[b].fractionOfTotal = static_cast<double>(result[b].count) / bytes.size();
	}
}

void FrequencyAnalysis::BytePairFrequencyAnalysis(const ByteVector & bytes, BytePairFrequencyMap & result)
{
	result.clear();
	if (bytes.size() < 2) {
		return;
	}
	size_t totalPairs = bytes.size() - 1;
	for (size_t i = 1; i < bytes.size(); ++i) {
		BytePair bytePair(bytes[i - 1], bytes[i]);
		result[bytePair].count++;
		result[bytePair].fractionOfTotal = static_cast<double>(result[bytePair].count) / totalPairs;
	}
}

bool EnglishStringToBytes(const std::string &str, ByteVector &bytes)
{
	bytes.clear();

	for (auto c : str) {
		if (!Utils::IsPrintable(c)) {
			return false;
		}
		if (Utils::IsAlpha(c)) {
			bytes.push_back(Utils::ToUpper(c));
		}
		else {
			bytes.push_back(c);
		}
	}

	return true;
}

bool FrequencyAnalysis::EnglishStringFrequencyAnalysis(const std::string &str, ByteFrequencyMap &result)
{
	ByteVector bytes;

	if (!EnglishStringToBytes(str, bytes)) {
		return false;
	}
	ByteFrequencyAnalysis(bytes, result);
	return true;
}

void FrequencyAnalysis::EnglishStringPairFrequencyAnalysis(const std::string &str, BytePairFrequencyMap &result)
{
	ByteVector bytes;

	EnglishStringToBytes(str, bytes);
	BytePairFrequencyAnalysis(bytes, result);
}

double FrequencyAnalysis::GetEnglishStringFrequencyScore(const std::string & str)
{
	ByteFrequencyMap freqMap;
	if (!EnglishStringFrequencyAnalysis(str, freqMap)) {
		return NAN;
	}

	double sumofsquares = 0;
	for (auto byteFreq : freqMap) {
		char c = (char)byteFreq.first;
		double englishCharFreq = GetEnglishCharFrequency(c);
		double diff = byteFreq.second.fractionOfTotal - englishCharFreq;
		sumofsquares += (diff * diff);
	}

	return sumofsquares / freqMap.size();
}

double FrequencyAnalysis::GetEnglishCharFrequency(char c)
{
	auto iter = ENGLISH_FREQ.find(Utils::ToUpper(c));
	if (iter == ENGLISH_FREQ.end()) {
		return 0.0;
	}
	return iter->second;
}
