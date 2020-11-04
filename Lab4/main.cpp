#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "FA.h"

using namespace std;

ifstream infile("input.txt");

FA transition_data_structure;

int min(size_t a, size_t b)
{
	if (a < b)
		return a;
	return b;
}

vector<string> getWordsSeparatedBySpace(string line) // get the list of tokens(separated by space) from a line(string) 
{
	vector<string> res;

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

int main()
{
	vector<string> states, final_states, alphabet;
	string initial_state;
	vector<string> transitions;
	string line;

	getline(infile, line); // read initial_state
	initial_state = line;

	getline(infile, line); // read final states
	final_states = getWordsSeparatedBySpace(line);

	getline(infile, line); // read other states, if they exists
	states = getWordsSeparatedBySpace(line);

	getline(infile, line); // read alphabet
	alphabet = getWordsSeparatedBySpace(line);

	getline(infile, line); // read transitions
	transitions = getWordsSeparatedBySpace(line);

	// set all the data that the FA needs
	transition_data_structure.setAllStates(initial_state, final_states, states);
	transition_data_structure.setAlphabet(alphabet);
	transition_data_structure.buildFA(transitions);

	if (transition_data_structure.deterministic())
		cout << "This is a DFA" << endl; // deterministic
	else cout << "This is a NDFA" << endl; // non-deterministic

	while (1) // loop menu
	{
		cout << "What would you like to print?" << endl;
		cout << "1. Initial state" << endl;
		cout << "2. Final states" << endl;
		cout << "3. Other states" << endl;
		cout << "4. Alphabet" << endl;
		cout << "5. Transitions" << endl;
		cout << "6. Exit" << endl;

		int option;
		cin >> option;

		if (option == 1)
		{
			transition_data_structure.display_initial_state();
		}
		else if (option == 2)
		{
			transition_data_structure.display_final_states();
		}
		else if (option == 3)
		{
			transition_data_structure.display_other_states();
		}
		else if (option == 4)
		{
			transition_data_structure.display_alphabet();
		}
		else if(option==5)
		{
			for (int i = 0; i < transitions.size(); i++)
				cout << transitions[i] << endl;
		}
		else if (option == 6)
		{
			break;
		}
		else cout << "Option unknown!" << endl;
	}

	cout << "Bye bye!";

	_getch();
	return 0;
}