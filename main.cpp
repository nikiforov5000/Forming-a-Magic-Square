#include "MagicSquare.h"

int findMinDiff(MagicSquare& sqMagic, MagicSquare& sample) {
	int min{ INT32_MAX };
	for (size_t i = 0; i < 4; ++i) {
		int temp = (sqMagic - sample).sum();
		min = std::min(temp, min);
		sample.rotate();
	}
	sample.flip();
	for (size_t i = 0; i < 4; ++i) {
		int temp = (sqMagic - sample).sum();
		min = std::min(temp, min);
		sample.rotate();
	}
	return min;
}

int main() {
	std::vector<std::vector<int>> sMagic{
		{ 4, 9, 2 },
		{ 3, 5, 7 },
		{ 8, 1, 6 } };
	std::vector<std::vector<int>> sSample1{
		{ 5, 3, 4 },
		{ 1, 5, 8 },
		{ 6, 4, 2 } };
	std::vector<std::vector<int>> sSample2{
		{ 4, 8, 2 },
		{ 4, 5, 7 },
		{ 6, 1, 6 } };
	std::vector<std::vector<int>> sMagic4{
		{  6,  3, 10, 15 },
		{  9, 16,  5,  4 },
		{  7,  2, 11, 14 },
		{ 12, 13,  8,  1 }
	};
	std::vector<std::vector<int>> sSample4{
		{  6,  3, 10, 14 },
		{  9, 16,  5,  6 },
		{  7,  2, 11, 11 },
		{ 12, 3,  8,  1 }
	};


	MagicSquare sqMagic4(sMagic4);
	MagicSquare sqSample4(sSample4);
	sqSample4.rotate();
	int result{ findMinDiff(sqMagic4, sqSample4) };
	std::cout << result << std::endl;


	return 0;
}