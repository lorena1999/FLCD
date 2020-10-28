#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>
#include "HashTable.h"
#include <string>
#include <string.h>
#include <fstream>
#include <map>
#include <cstdlib>
#include <algorithm>
#include<regex>
#include <regex>
#include "Scanner.h"

using namespace std;

Scanner::Scanner()
{
	line_counter = 0;
}

string Scanner::convertToString(char *a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

char * Scanner::strtok_new(char * string, char const * delimiter)
{
	static char *source = NULL;
	char *p, *riturn = 0;
	if (string != NULL)         source = string;
	if (source == NULL)         return NULL;

	if ((p = strpbrk(source, delimiter)) != NULL) {
		*p = 0;
		riturn = source;
		source = ++p;
	}
	return riturn;
}

string Scanner::ltrim(const std::string& s)
{
	static const regex lws{ "^[[:space:]]*", std::regex_constants::extended };
	return regex_replace(s, lws, "");
}

string Scanner::rtrim(const std::string& s)
{
	static const regex tws{ "[[:space:]]*$", std::regex_constants::extended };
	return regex_replace(s, tws, "");
}

void Scanner::scan()
{
	string line;
	ifstream myFile("pb2.txt"); // file to read from

	vector<string> reserved_words = { "let", "while", "if", "do", "elif", "ret", "else", "integer", "double", "char", "boolean", "write", "read", "string", "for" };
	vector<string> digits = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	if (myFile.is_open())
	{
		while (getline(myFile, line)) // read line by line from file
		{

			line_counter++;

			int cnt = 0; // counter which counts the number of " characters from a row
			int cnt_charq = 0; // counter which counts the number of ' characters from a row

			char str[100];
			char *pch;

			strcpy(str, line.c_str());

			pch = strtok_new(str, " ()\",;!=%/-+<&>[]{}:*'"); // reading delimitators

			bool started = false;
			bool finished = false;
			string ss = "";

			bool started_c = false;
			bool finished_c = false;

			string last_delim = "x";
			string last_thing = "none";
			string sign = "none";

			bool is_mistake = true;

			while (pch != NULL)
			{

				bool added = false;
				bool added2 = false;

				string delim_to_add = "";
				bool semic = false;

				string s = convertToString(pch, strlen(pch)); // convert token to string

				s = ltrim(rtrim(s));

				char delim_used = line[pch - str + strlen(pch)];
				string delim = "";
				delim += delim_used;

				for (int i = 0; i < reserved_words.size(); i++) // check for reserved words
				{
					if (s == reserved_words[i])
					{
						pif.push_back({ s,-1 });
						added2 = true;
						is_mistake = false;
					}
				}

				if (delim_used != ' ') // space doesnt count
				{


					bool added_diff = false;

					if ((last_delim == "!" && delim_used == '=') || (last_delim == "<" && delim_used == '=') || (last_delim == "&" && delim_used == '&') || (last_delim == ">" && delim_used == '=')) // prepare for composite operators
					{
						if (delim_used == '=')
						{
							pif.pop_back();
							pif.push_back({ last_delim + "=", -1 });
							last_thing == "delim";
							added_diff = true;
							added == true;
						}
						else if (delim_used == '&')
						{
							pif.pop_back();
							pif.push_back({ "&&", -1 });
							last_thing == "delim";
							added_diff = true;
							added == true;
						}
						else
						{
							added_diff = false;
							added = false;
						}
					}

					if (added == true && delim_used == ';')
					{
						semic = true;
					}

					if (delim_used != '"' && added_diff == false && started == false && delim_used != '\'' && added == false) //generic case
					{
						if (delim_used != '-' && delim_used != '+')
						{
							delim_to_add = delim;
							added = true;
						}
					}


					if (delim_used == '\'') // char case
					{
						cnt_charq++;

						if (started_c == false) // beginning
						{
							added = true;
							started_c = true;
						}
						else // end
						{
							if (s.length() != 1)
							{
								cout << "Lexical error on line " << line_counter << endl;
								cout << "Details: Char value should be of length one" << endl;
								return;
							}
							added = true;
							hashy.AddValue("'" + s + "'");
							pif.push_back({ "const", hashy.FindValue("'" + s + "'") });
							is_mistake = false;
							last_thing == "elem";
							started_c = finished_c = false;
						}
					}


					if (delim_used == '"' && started == false) // start string
					{
						started = true;
						ss = '"';
						ss += s;
						added = true;
						cnt++;

					}
					else if (delim_used == '"' && started == true && finished == false) // end string
					{
						finished = false;
						started = false;
						ss += s;
						ss += '"';
						cnt++;

						hashy.AddValue(ss);
						pif.push_back({ "const", hashy.FindValue(ss) });
						is_mistake = false;
						last_thing = "elem";
						added = true;

					}
					last_delim = delim_used;

				}

				if (delim_used != '"' && started == true && finished == false) // middle string
				{
					added = true;
					ss += s + delim_used;
				}

				bool third_try = false;
				bool id_to_add = false;

				if (s == "0") // check if we have 0 as a number 
				{
					if (last_thing == "delim" && sign != "none") // if 0 has its own sign => error
					{
						cout << "Lexical error on line " << line_counter << endl;
						cout << "Details: 0 is unsigned!" << endl;
						return;
					}
				}

				if (added2 == false) // if wasnt added at all
				{
					if (delim == "-" || delim == "+")
					{
						sign = delim_used;
					}

					string nr = "";
					regex str_expr("0|([1-9][0-9]*)"); // regex for integer constant corrections
					regex str_expr_double("^[0-9]+(\\.[0-9]+)+$"); // regex for double constants corrections

					if (regex_match(s, str_expr) || regex_match(s, str_expr_double))
					{
						cout << "FACE MATCH "<<s << endl;
						if (sign != "none") // check if it has sign
							nr = sign + s;
						else
							nr = s;
					}

					if (nr != "")
					{
						bool added_s = false;
						if (last_thing == "elem" && sign != "none")
						{
							pif.push_back({ sign, -1 }); // sign here is an operator
							sign = "none";
							added_s = true;
						}

						if (added_s == true)
						{
							hashy.AddValue(s);
							pif.push_back({ "const" ,hashy.FindValue(s) });
							is_mistake = false;
							sign = "none";
						}
						else
						{
							hashy.AddValue(nr);
							pif.push_back({ "const" ,hashy.FindValue(nr) });
							is_mistake = false;
							sign = "none";
						}

						last_thing = "elem"; // remember the last thing we added in pif
						third_try = true;
					}

					if (third_try == false && sign != "none")
						id_to_add = true;
				}

				if (third_try == false && added2 == false && s != "" && started == false && added2 == false && delim_used != '"' && delim_used != '\'')
				{

					regex str_expr("0[0-9][0-9]*"); // regex for incorrectness of an integer

					if (regex_match(s, str_expr)) // if matches => number starts with 0 and has more than one digit => error
					{
						cout << "Lexical error on line " << line_counter << endl;
						cout << "Details: integer cannot start with 0 " << endl;
						return;
					}

					regex str_expr_2("[0-9][a-zA-Z0-9_]*"); // regex for incorrectness of an identifier

					if (regex_match(s, str_expr_2)) // if match => identifier starts with digit => error
					{
						cout << "Lexical error on line " << line_counter << endl;
						cout << "Details: identifier cannot start with digit " << endl;
						return;
					}

					if (last_thing == "delim")
					{
						hashy.AddValue(s);
						pif.push_back({ "id", hashy.FindValue(s) });
						is_mistake = false;
						last_thing = "elem";

						if (id_to_add)
							pif.push_back({ sign, -1 });
					}
					else
					{
						if (id_to_add)
							pif.push_back({ sign, -1 });

						hashy.AddValue(s);
						pif.push_back({ "id", hashy.FindValue(s) });
						last_thing = "elem";
						is_mistake = false;
					}

					if (s != "")
						sign = "none";
				}

				if (semic == true)
				{
					pif.push_back({ ";",-1 });
					last_thing = "delim";
				}

				if (delim_to_add != " " && delim_to_add != "")
				{
					pif.push_back({ delim_to_add, -1 });
					last_thing = "delim";
				}
				pch = strtok_new(NULL, " ()\",;!=%/-+<&>[]{}*:'"); // get the next token
			}

			// if quotes aren't all closed on a row => error
			if (cnt % 2 != 0)
			{
				cout << "Lexical error on line " << line_counter << endl;
				cout << "Detalis: String double quotest must be closed!" << endl;
				return;
			}

			if (cnt_charq % 2 != 0)
			{
				cout << "Lexical error on line " << line_counter << endl;
				cout << "Details: Char single quotes must be closed!" << endl;
				return;
			}

		}
		myFile.close();

		cout << "PIF" << endl << endl;

		for (int i = 0; i < pif.size(); i++)
		{
			cout << '\t' << pif[i].first << '\t' << pif[i].second << '\n';
		}

		hashy.printTable();

	}
	else cout << "Unable to open file";
}
