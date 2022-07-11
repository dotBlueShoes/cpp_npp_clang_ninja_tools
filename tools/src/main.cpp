#include "Framework.hpp"
#include "NppProcessor.hpp"

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


std::string parseSecret(std::string line, const string projectPath) {
	const string projectPathToken { "project_path" };
	bool isToken { false };
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
	const string originPath { ".ninja\\secret.ninja" } ,
		resultPath { ".ninja\\_secret.ninja" };
	
	vector<string> data;
	string line;

	ifstream originFile(originPath);
	ofstream resultFile(resultPath);

	
	if (originFile.is_open() && resultFile.is_open()) {
		
		// READ
		while (getline(originFile, line))
			data.push_back(line);
		originFile.close();
		
		// WRITE
		for (size_t i = 0; i < data.size(); i++)
			resultFile << parseSecret(data[i], projectPath);
		resultFile.close();
		
		// REPLACE (Is this the safest way?)
		if (filesystem::remove(originPath)) {
			filesystem::rename(resultPath, originPath);
			return 0;
		}
		
	} else 
		std::cerr << "Error: Opening or creating the file.\n";
	
	std::cerr << "Error: Removing old file.\n";
	return 1;
}

// Specific to windows unicode main function.
// int wmain(int argumentsLength, wchar_t* arguments[])

namespace tokens {
	const string 
		setupFull = "--setup", setupShort = "-s",
		reprojectFull = "--refresh-npp", reprojectShort = "-r";
}
	
int main(const int argumentsLength, const char** arguments) {
	bool isEqual = true;
	
	//std::cout << "ProjectPath = "<< arguments[2] << "\\\n";
	
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::setupFull[i]) {
			isEqual = false;
			break;
		}
		
	if (isEqual) { setup(arguments[2]); return 0; }
	isEqual = true;
		
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::setupShort[i]) {
			isEqual = false;
			break;
		}
		
	if (isEqual) { setup(arguments[2]); return 0; }
	isEqual = true;
	
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::reprojectFull[i]) {
			isEqual = false;
			break;
		}
		
	if (isEqual) { 
		const char* projects[] { arguments[3], arguments[4] }; 
		NppProcessor::refreshNpp(arguments[2], argumentsLength - 3, projects); 
		return 0;
	} isEqual = true;
		
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::reprojectShort[i]) {
			isEqual = false;
			break;
		}
		
	if (isEqual) { 
		const char* projects[] { arguments[3], arguments[4] }; 
		NppProcessor::refreshNpp(arguments[2], argumentsLength - 3, projects); 
		return 0;
	}
	
	
	std::cin.get();
	return 0;
}