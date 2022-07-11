#pragma once
#include <string>
#include <vector>

class sample {
	int value;
public:
	sample(int newValue) : value(newValue) {};
	const int& getValue() const;
	
	// tokenizacja - przypadki
	
	int tokens_1() {
		
		// same result:
		//  np. mamy tokeny: "--setup", i "-s" i teoretycznie możemy napotkać inne.
		//  wiadomo że obie te komendy znaczą to samo, a więc
		//  chcemy aby sprowadzały się do tego samego kodu wykonywalnego.
		//  oba te stringi są jednak różnej długości
		//
	
		//bool isEqual;
		//for (size_t i = 0; i != '\0'; i++) {
		//	isEqual = false;
		//	
		//	if (arguments[1][i] == tokens::setupFull[i])
		//		isEqual = true;
		//	
		//	if (arguments[1][i] == tokens::setupShort[i])
		//		isEqual = true;
		//	
		//	if (!isEqual) return 1; // Not equal status
		//}
	
		// but... what is someone would pass into "-ssetup" or "--".. 
		//  it would be a bug.
	
		//setup(arguments[2]);
		return 0;
	}
	
	int tokens_2() {
		
		// same result treated as different using mask:
		//const int 
		//	setupFullBit = 0b1000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000,
		//	setupShortBit = 0b0100.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000;
		//int equalMask = 0b0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000.0000;
		//for (size_t i = 0; i != '\0'; i++) {
			
		//	if (arguments[1][i] == tokens::setupFull[i])
		//		equalMask ~= setupFullBit;
		//	
		//	if (arguments[1][i] == tokens::setupShort[i])
		//		equalMask ~= setupShortBit;
		//}
		
		return 0;
	}
	
};