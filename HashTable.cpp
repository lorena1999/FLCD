#include <iostream>
#include <string>
#include <cstring>
#include "HashTable.h"

using namespace std;

HashTable::HashTable()
{
	arr.assign(capacity, ""); // initialization
}


int HashTable::AddValue(string identifier)
{
	int fv = FindValue(identifier);
	if (fv != -1)
	{
		return fv;
	}

	if (size / capacity > 0.7)
	{
		capacity *= 2;
		size = 0;

		vector<string> copy_arr;
		copy_arr.assign(capacity/2, ""); 

		for (int i = 0; i < capacity / 2; i++) // copy initial vector
			copy_arr[i] = arr[i];

		arr.clear();

		arr.assign(capacity, ""); // double capacity

		for (int i = 0; i < capacity / 2; i++) // reassigning
			AddValue(copy_arr[i]);

	}

	int index = Hash(identifier);
	while (index < capacity && arr[index] != "")
		index++;

	if (index == capacity)
		index = 0; // start from the beginning

	while (index < capacity && arr[index] != "")
		index++;
	

	arr[index] = identifier; // add new value
	size++;

	return index;
}


int HashTable::FindValue(string key)
{
	int index = Hash(key);

	while (index < capacity && arr[index] != key)
		index++;

	if (index == capacity)
		index = 0;

	while (index < capacity && arr[index] != key)
		index++;

	if (index == capacity)
		return -1; // didnt find anything

	if (arr[index] == key)
		return index; // return the index of the identifier

	return -1;

}

void HashTable::printTable()
{
	cout << endl << "Symbol Table: " << endl << endl;
	for (int i = 0; i < capacity; i++)
	{
		if (arr[i] != "")
		{
			cout << arr[i] << " " << Hash(arr[i]) << endl;
		}
	}
}

int HashTable::Hash(string key) // ascii sum of the given string modulo capacity
{
	int hash = 0;
	int index;

	index = key.length();

	for (int i = 0; i < key.length(); i++)
	{
		hash = hash + (int)key[i]; 
	}

	index = hash % capacity;

	return index;

}