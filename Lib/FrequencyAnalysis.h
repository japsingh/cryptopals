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
};