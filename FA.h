#pragma once
#include "FA.h"
#include <list>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#ifndef FA_H
#define FA_H

#endif // !FA_H

class FA
{
private:
	map<pair<string, string>, string> mymap; // map which holds transitions
	string initial_state;
	vector<string> final_states;
	vector<string> other_states;
	vector<string> alphabet;
	bool is_deterministic = true;
	bool is_key_already(string s1, string sym); // find if a pair of type (state,symbol) exists already in the transitions 
	vector<string> getWordsSeparatedBySpace(string line);
	int min(size_t a, size_t b);

public:
	FA(); // constructor
	void setAllStates(string inital_states, vector<string> final_states, vector<string> other_states);
	void setAlphabet(vector<string> alphabet);
	void AddTransition(string s1, string sym, string s2);
	string FindNextTransition(string s1, string sym);
	void display_transitions();
	bool deterministic();
	void display_alphabet();
	void display_initial_state();
	void display_final_states();
	void display_other_states();
	void buildFA(vector<string> transitions); // build the transitions map 
	bool checkSequence(string seq);
	void read_from_file(string fileName);

};