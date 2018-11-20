#pragma once
#include "Types.h"
#include <map>

class FrequencyAnalysis
{
public:
	struct Stats
	{
		size_t count;
		double fractionOfTotal;
	};
	typedef std::map<byte_t, Stats> ByteFrequencyMap;
	typedef std::map<BytePair, Stats> BytePairFrequencyMap;

	static void ByteFrequencyAnalysis(const ByteVector &bytes, ByteFrequencyMap &result);
	static void BytePairFrequencyAnalysis(const ByteVector &bytes, BytePairFrequencyMap &result);

	static double GetEnglishCharFrequency(char c);

	static bool EnglishStringFrequencyAnalysis(const std::string &str, ByteFrequencyMap &result);
	static void EnglishStringPairFrequencyAnalysis(const std::string &str, BytePairFrequencyMap &result);
	static double GetEnglishStringFrequencyScore(const std::string &str);
};