#include <iostream>
#include <string>
#include <cstring>
#include "FA.h"
#include <set>
#include <fstream>

using namespace std;

FA::FA()
{

}

int FA::min(size_t a, size_t b)
{
	if (a < b)
		return a;
	return b;
}

vector<string> FA::getWordsSeparatedBySpace(string line) // get the list of tokens(separated by space) from a line(string) 
{
	vector<string> res;

	if (line == "null")
	{
		return res;
	}

	size_t pos = line.find(" ");
	size_t initialPos = 0;

	while (pos != string::npos)
	{
		res.push_back(line.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = line.find(" ", initialPos);
	}

	res.push_back(line.substr(initialPos, min(pos, line.size()) - initialPos + 1));

	return res;
}

void FA::read_from_file(string fileName)
{
	ifstream infile(fileName);

	string line, initial_sstate;
	vector<string> states, final_states, alphabet;
	vector<string> transitions;

	getline(infile, line); // read initial_state
	initial_sstate = line;

	getline(infile, line); // read final states
	final_states = getWordsSeparatedBySpace(line);

	getline(infile, line); // read other states, if they exists
	states = getWordsSeparatedBySpace(line);

	getline(infile, line); // read alphabet
	alphabet = getWordsSeparatedBySpace(line);

	getline(infile, line); // read transitions
	transitions = getWordsSeparatedBySpace(line);

	setAllStates(initial_sstate, final_states, states);
	setAlphabet(alphabet);
	buildFA(transitions);

}

void FA::setAllStates(string initial_states, vector<string> final_states, vector<string> other_states)
{
	this->initial_state = initial_states;

	set<string> s(final_states.begin(), final_states.end()); // make sure there are no duplicates
	this->final_states.assign(s.begin(), s.end());

	set<string> s2(other_states.begin(), other_states.end()); // make sure there are no duplicates
	this->other_states.assign(s2.begin(), s2.end());
}

void FA::setAlphabet(vector<string> alphabet)
{
	this->alphabet = alphabet;
}

void FA::display_alphabet()
{
	for (int i = 0; i < this->alphabet.size(); i++)
	{
		cout << this->alphabet[i] << endl;
	}
}

void FA::display_initial_state()
{
	cout << this->initial_state << endl;
}

void FA::display_final_states()
{
	for (int i = 0; i < this->final_states.size(); i++)
	{
		cout << this->final_states[i] << endl;
	}
}

void FA::display_other_states()
{
	for (int i = 0; i < this->other_states.size(); i++)
	{
		cout << this->other_states[i] << endl;
	}
}

bool FA::is_key_already(string s1, string sym)
{
	auto it = mymap.find({ s1,sym });
	if (it != mymap.end())
		return true;
	return false;
}

void FA::buildFA(vector<string> transitions)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		string s1 = "", sym = "", s2 = "";
		s1 += transitions[i][1];
		sym += transitions[i][3];
		s2 += transitions[i][6];
		AddTransition(s1, sym, s2);
	}
}

void FA::AddTransition(string s1, string sym, string s2)
{
	if (is_key_already(s1, sym))
		this->is_deterministic = false;
	this->mymap.insert({ { s1,sym },s2 });
}

bool FA::deterministic()
{
	return this->is_deterministic;
}

bool FA::checkSequence(string seq)
{
	if (!is_deterministic)
		return false;

	string current = this->initial_state;

	for (int i = 0; i < seq.length(); i++)
	{
		string letter = "";
		letter += seq[i];

		bool found = false;

		for (auto it = mymap.begin(); it != mymap.end(); it++)
		{
			if (it->first.first == current)
			{
				if (it->first.second == letter)
				{
					current = it->second;
					found = true;
					break;
				}
			}
		}

		if (found == false)
			return false;
	}

	for (int i = 0; i < final_states.size(); i++)
		if (final_states[i] == current)
			return true;

	return false;
}

string FA::FindNextTransition(string s1, string sym)
{
	auto itr = this->mymap.find({ s1,sym });
	return itr->second;
}

void FA::display_transitions()
{
	for (auto it = mymap.begin(); it != mymap.end(); it++)
	{
		cout << "(" << it->first.first << "," << it->first.second << ")" << "=" << it->second << endl;
	}

}