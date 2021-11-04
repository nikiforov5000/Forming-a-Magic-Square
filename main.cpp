#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class MagicSquare {
	std::vector<std::vector<int>> m_s{};
	size_t m_size{};
public:
	MagicSquare() {
	}
	MagicSquare(size_t size) :m_size(size) {
		m_s = std::vector<std::vector<int>>(size, std::vector<int>(size, -1));
	}
	MagicSquare(MagicSquare&& s) noexcept :
		m_s(std::move(s.m_s)),
		m_size(std::exchange(s.m_size, 0))
	{}
	MagicSquare(std::vector<std::vector<int>>& s) :m_s(s) {
		for (auto row : s) {
			if (row.size() != s.size()) {
				throw std::exception("[BAD INPUT] Sides are not equal.");
			}
		}
		m_size = m_s.size();
	}
	int getValue(size_t i, size_t j) {
		return m_s[i][j];
	}
	void setValue(size_t i, size_t j, int val) {
		m_s[i][j] = val;
	}
	size_t getSize() {
		return m_s.size();
	}
	template<typename T>
	T forEach(void (*f)(int* data) = 0, T t = 0) {
		for (size_t i = 0; i < m_size; ++i) {
			for (size_t j = 0; j < m_size; ++j) {
				if (f) {
					f(&m_s[i][j]);
				}
				t += m_s[i][j];
			}
		}
		return t;
	}
	friend MagicSquare operator-(MagicSquare&, MagicSquare&);
	int sum() {
		return forEach<int>();
	}
	void rotate() {
		MagicSquare temp(m_size);
		for (size_t i = 0, k = m_size - 1; i < m_size; ++i, --k) {
			for (size_t j = 0, l = 0; j < m_size; ++j, ++l) {
				temp.m_s[l][k] = m_s[i][j];
			}
		}
		m_s = std::move(temp.m_s);
	}
	void flip() {
		std::reverse(m_s.begin(), m_s.end());
	}
	~MagicSquare() {
	}
	MagicSquare& operator=(MagicSquare&& s1) noexcept {
		if (this == &s1) {
			return *this;
		}
		m_s = std::exchange(s1.m_s, m_s);
		m_size = std::exchange(s1.m_size, 0);
		return *this;
	}
};

MagicSquare operator-(MagicSquare& lhs, MagicSquare& rhs) {
	MagicSquare result(lhs.getSize());
	int temp{};
	for (size_t i = 0; i < lhs.getSize(); ++i) {
		for (size_t j = 0; j < lhs.getSize(); ++j) {
			temp = std::abs(lhs.getValue(i, j) - rhs.getValue(i, j));
			result.setValue(i, j, temp);
		}
	}
	return result;
}

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