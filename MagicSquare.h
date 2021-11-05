#pragma once
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <utility>
#include <vector>
class MagicSquare {
	std::vector<std::vector<int>> m_s{};
	size_t m_size{};
public:
	MagicSquare() {};
	MagicSquare(size_t size);
	MagicSquare(MagicSquare&& s) noexcept ;
	MagicSquare(std::vector<std::vector<int>>& s);
	int getValue(size_t i, size_t j) { return m_s[i][j]; }
	void setValue(size_t i, size_t j, int val) { m_s[i][j] = val; }
	size_t getSize() { return m_s.size(); }
	friend MagicSquare operator-(MagicSquare&, MagicSquare&);
	int sum();
	void rotate();
	void flip();
	~MagicSquare() {};
	MagicSquare& operator=(MagicSquare&& s1)noexcept;
};

