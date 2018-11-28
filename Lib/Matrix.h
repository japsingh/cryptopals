#pragma once
#include <vector>

class Matrix
{
public:
	template <class T> static bool Convert1dTo2d(const std::vector<T> &src, size_t nCols, std::vector<std::vector<T>> &dest);
	template <class T> static bool Transpose(const std::vector<std::vector<T>> &src, std::vector<std::vector<T>> &dest);
};

template<class T>
inline bool Matrix::Convert1dTo2d(const std::vector<T> &src, size_t nCols, std::vector<std::vector<T>> &dest)
{
	// source 1d array size should be divisible by nCols to avoid padding unnecessary characters
	if ((src.size() % nCols) != 0) {
		return false;
	}

	for (size_t i = 0; i < src.size(); i += nCols) {
		std::vector<T> curRow;
		for (size_t curOffset = i; curOffset < (i + nCols) && curOffset < src.size(); ++curOffset) {
			curRow.push_back(src[curOffset]);
		}

		dest.push_back(curRow);
	}

	return true;
}

template<class T>
inline bool Matrix::Transpose(const std::vector<std::vector<T>>& src, std::vector<std::vector<T>>& dest)
{
	dest.clear();

	if (src.empty()) {
		return true;
	}

	// Allocate number of rows in dest equal to cols in src
	// Allocate number of cols in each row of dest equal to rows in src
	for (size_t i = 0; i < src[0].size(); ++i) {
		std::vector<T> destRow;
		destRow.resize(src.size());
		dest.push_back(destRow);
	}

	// Now assign values
	for (size_t i = 0; i < src.size(); ++i) {
		for (size_t j = 0; j < src[i].size(); ++j) {
			dest[j][i] = src[i][j];
		}
	}

	return true;
}
