#pragma once
#include "HashTable.h"
#include <list>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#ifndef HashTable_H
#define HashTable_H

#endif // !HashTable_H

class HashTable
{
private:

	int capacity = 1000;
	int size = 0;
	vector<string> arr;
	int Hash(string key);


public:
	HashTable(); // constructor
	int AddValue(string identifier); 
	int FindValue(string key);
	void printTable();
};