#include "MagicSquare.h"
MagicSquare::MagicSquare(size_t size) :m_size(size) {
	m_s = std::vector<std::vector<int>>(size, std::vector<int>(size, -1));
}
MagicSquare::MagicSquare(MagicSquare&& s) noexcept {
	m_s = std::move(s.m_s);
	m_size = std::exchange(s.m_size, 0);
}

MagicSquare::MagicSquare(std::vector<std::vector<int>>& s) :m_s(s) {
	for (auto row : s) {
		if (row.size() != s.size()) {
			throw std::exception("[BAD INPUT] Sides are not equal.");
		}
	}
	m_size = m_s.size();
}
int MagicSquare::sum() {
	int sum{};
	for (auto row : m_s) { for (int x : row) { sum += x; } }
	return sum;
}

void MagicSquare::rotate() {
	MagicSquare temp(m_size);
	for (size_t i = 0, k = m_size - 1; i < m_size; ++i, --k) {
		for (size_t j = 0, l = 0; j < m_size; ++j, ++l) {
			temp.m_s[l][k] = m_s[i][j];
		}
	}
	m_s = std::move(temp.m_s);
}
void MagicSquare::flip() {
	std::reverse(m_s.begin(), m_s.end());
}
MagicSquare& MagicSquare::operator=(MagicSquare&& s1) noexcept {
	if (this == &s1) {
		return *this;
	}
	m_s = std::exchange(s1.m_s, m_s);
	m_size = std::exchange(s1.m_size, 0);
	return *this;
}

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