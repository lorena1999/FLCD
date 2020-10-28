#pragma once
#include "Scanner.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "HashTable.h"

using namespace std;


#ifndef Scanner_H
#define Scanner_H

#endif // !Scanner_H

class Scanner
{
private: 
	string convertToString(char *a, int size); // convert from char to string
	char *strtok_new(char * string, char const * delimiter); // trim spaces from left and right of the string 
	string ltrim(const std::string& s); // left trim spaces
	string rtrim(const std::string& s); // right trim spaces
	vector<pair<string, int>> pif;
	HashTable hashy; // symTable
	
public:
	int line_counter;
	Scanner(); // constructor
	void scan();
	vector<pair<string, int>> getPif();
	HashTable getSymTbl();
	void printPif();
	void printSymTbl();


};