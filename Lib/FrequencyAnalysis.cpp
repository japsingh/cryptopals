#include "stdafx.h"
#include "FrequencyAnalysis.h"

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
