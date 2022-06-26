#include <iostream>
#include <windows.h>
#include <iostream>
#include "sample.hpp"
#include "lib_sample.hpp"

// devel

int main() {
	char value = 0;
	
	sample something1(5);
	lib_sample something2(5);
	
	std::cout << std::to_string(something1.getValue());
	std::cout << std::to_string(something2.getValue());
	
	// SetConsoleTitle(T("Some title"));
	SetConsoleTitleA("WOOHOO");
	
	std::cin >> value;
	return 0;
}