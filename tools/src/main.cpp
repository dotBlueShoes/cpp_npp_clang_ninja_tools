#include "Framework.hpp"
#include "NppProcessor.hpp"

/// TODO
/// 1. Make it so tools can generate new projects based on the cpp_npp_clang_ninja setup.
/// 2. Think about including mold in it.

// 1. re-create tools.npp file so it will contain all the files there are in those folders.
// 2. setup script that will
//  - ask the user for:
//    - project name
//    - build name
//    - libs
//  - will setup project path
// 3. uppercase support.

// Error checking
// output
// If in file defined variables would be always in the same order 
//  the parse function could work as more then a 1 function that would be 
//  changed constanly in a loop for functions to look for other tokens. 
//  Also yeah that can be easier implemented... 

string parseSecret(
	string line, 
	const string projectPath
) {
	const string projectPathToken { "projectPath" };
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
		temp += projectPathToken;
		temp +=	" = ";
		temp += projectPath;
		temp += "\n";
		return temp;
	}
	
	line += '\n';
	return line ;
}

int DisplayHelp() {
	std::cout << "Tools\n"
		"-h, --help 		: help\n"
		"-s, --setup 		: setup\n"
		"-r, --refresh-npp	: refresh" << std::endl;
	return 0;
}

int setup(
	const string projectPath
) {
	const string originPath { ".ninja\\secret.ninja" },
		resultPath { ".ninja\\_secret.ninja" };
	
	vector<string> data;
	string line;
	
	std::cout << projectPath << '\n';

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
	return 0;
}

// Specific to windows unicode main function.
// int wmain(int argumentsLength, wchar_t* arguments[])

namespace tokens {
	
	const string 
		helpFull = "--help", helpShort = "-h",
		setupFull = "--setup", setupShort = "-s",
		reprojectFull = "--refresh-npp", reprojectShort = "-r";
		
	const string tokens[] {
		helpFull, helpShort,
		setupFull, setupShort,
		reprojectFull, reprojectShort,
	};
	
}
	
int main(
	const int argumentsLength, 
	const char** arguments
) {
	bool isToken = true;
	
	if (argumentsLength == 1) {
		DisplayHelp();
		return 0;
	}
	
	// COMMAND "--help"
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[0][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { DisplayHelp(); }
	
	// COMMAND "-h"
	isToken = true;
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[1][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { DisplayHelp(); }
	
	// COMMAND "--setup"
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[2][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { setup(arguments[2]); return 0; }
	
	// COMMAND "-s"
	isToken = true;
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[3][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { setup(arguments[2]); return 0; }
	
	
	// COMMAND "--refresh-npp"
	isToken = true;
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[4][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { 
		const char* projects[] { arguments[3], arguments[4] }; 
		{ using namespace NppProcessor;
			refreshNpp(arguments[2], argumentsLength - 3, projects); 
		}
		return 0;
	} 
	
	// COMMAND "-r"
	isToken = true;
	for (size_t i = 0; arguments[1][i] != '\0'; i++)
		if (arguments[1][i] != tokens::tokens[5][i]) {
			isToken = false;
			break;
		}
		
	if (isToken) { 
		const char* projects[] { arguments[3], arguments[4] }; 
		{ using namespace NppProcessor;
			refreshNpp(arguments[2], argumentsLength - 3, projects); 
		}
		return 0;
	}
	
	return 0;
}