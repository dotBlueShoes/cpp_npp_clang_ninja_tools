#pragma once
#include <string>
#include <vector>

class sample {
	int value;
public:
	sample(int newValue) : value(newValue) {};
	const int& getValue() const;
};