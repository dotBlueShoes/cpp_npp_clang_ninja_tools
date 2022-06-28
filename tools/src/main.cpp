#include <filesystem>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "sample.hpp"
#include "lib_sample.hpp"

// 1. re-create tools.npp file so it will contain all the files there are in those folders.
// 2. setup script that will
//  - ask the user for:
//    - project name
//    - build name
//    - libs
//  - will setup project path

// Error checking
// output
// If in file defined variables would be always in the same order 
//  the parse function could work as more then a 1 function that would be 
//  changed constanly in a loop for functions to look for other tokens. 
//  Also yeah that can be easier implemented... 

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

std::string parse(std::string line, const string projectPath) {
	const string projectPathToken = "project_path";
	bool isToken = false;
	size_t i = 0;
	
	for (; i < projectPathToken.length(); i++) {
		if (line[i] == projectPathToken[i]) isToken = true;
		else { 
			isToken = false; 
			break; 
		}
	}
	
	if (isToken) {
		string temp;
		temp += "project_path = ";
		temp += projectPath;
		temp += "\\\n";
		return temp;
	}
	
	line += '\n';
	return line ;
}

int setup(const string projectPath) {
	const string originPath = ".ninja\\secret.ninja",
		resultPath = ".ninja\\_secret.ninja";
	
	vector<string> data;
	string line;

	ifstream originFile(originPath);
	ofstream resultFile(resultPath);

	// READ
	if (originFile.is_open()) {
		while (getline(originFile, line))
			data.push_back(line);
		originFile.close();
	} else std::cout << "File-Open-Error\n";

	// WRITE
	for (size_t i = 0; i < data.size(); i++)
		resultFile << parse(data[i], projectPath);
	resultFile.close();
	
	// REPLACE (Is this the safest way?)
	std::filesystem::remove(originPath);
	std::filesystem::rename(resultPath, originPath);
	
	return 0;
}

// Specific to windows unicode main function.
// int wmain(int argumentsLength, wchar_t* arguments[])
	
int main(int argumentsLength, char* arguments[]) {
	std::cout << "ProjectPath = "<< arguments[1] << "\\\n";
	
	setup(arguments[1]);
	
	std::cin.get();
	return 0;
}