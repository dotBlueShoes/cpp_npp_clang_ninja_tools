#include <iostream>
#include <windows.h>
#include <fstream>

#include "sample.hpp"
#include "lib_sample.hpp"

// 1. re-create tools.npp file so it will contain all the files there are in those folders.
// 2. setup script that will
//  - ask the user for:
//    - project name
//    - build name
//    - libs
//  - will setup project path

using std::fstream;
using std::string;

int setup() {
	const string projectPathToken = "project_path";
	
	fstream secretFile(".ninja\\secret.ninja");
	string currentLine;
	
	if (secretFile.is_open())
		
		while (getline(secretFile, currentLine)) {
			std::cout << currentLine << '\n';
			for (size_t i = 0; i < projectPathToken.length(); i++)
				if (!(currentLine[i] == projectPathToken[i])) break;
				else std::cout << "T";
				// get eqaul sign with or witout spaces and write after that logic.
		} 
		
	else {
		std::cout << "ERROR : File not found!";
	}
	
	secretFile.close();
	return 0;
}

int main() {
	setup();
	std::cin.get();
	return 0;
}