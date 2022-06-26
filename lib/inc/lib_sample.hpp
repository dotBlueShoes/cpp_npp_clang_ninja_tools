#pragma once
#include <string>
#include <vector>

// what

class lib_sample {
	int value;
public:
	lib_sample(int newValue) : value(newValue) {};
	const int& getValue() const;
};