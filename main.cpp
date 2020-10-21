#include <iostream>
#include <conio.h>
#include "HashTable.h"
#include <cstring>
#include <string>
#include <string.h>
#include <fstream>
#include <map>
#include <cstdlib>


using namespace std;


string convertToString(char *a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

int main()
{
	vector<pair<string, int>> pif;
	HashTable hashy;

	string line;
	ifstream myFile("pb2.txt");

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{

			char str[100];
			char *pch;

			strcpy(str, line.c_str());
			rsize_t strmax = sizeof(str);

			pch = strtok(str, " ");

			bool started = false;
			bool finished = false;
			string ss = "";


			while (pch != NULL)
			{
				string s = convertToString(pch, strlen(pch));
				bool added = false;

				if (s[0]=='\"')
				{
					ss = s;
					started = true;
				}
				else if (started == true && finished==false)
				{
					ss = ss + " " + s;
					if (s[s.length() - 1] == '\"')
					{
						finished = false;
						started = false;
						hashy.AddValue(ss);
						pif.push_back(pair<string, int>(ss, hashy.FindValue(ss)));
						added = true;
						ss = "";
					}

				}
				if ((s == "(" || s == ")" || s == ";" || s == ":" || s == "," || s == "=" || s == "let" || s == "if" || s == "while" || s == "elif" || s == "integer" || s == "double" || s == "char") && added == false)
					pif.push_back(pair<string, int>(s, -1));
				else
				{
					if (added == false && started==false)
					{
						bool added_here = false;
						if (s[0] == '+' || s[0] == '-')
						{
							if (s[1] != '0')
							{
								bool ok = true;
								for (int j = 1; j < s.length(); j++)
								{
									if (j == 1)
									{
										if (s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9')
											continue;
									}
									else
									{
										if (s[j] == '0' || s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9')
											continue;
									}
									
									ok = false;
									break;

								}
								if (ok == true)
								{
									hashy.AddValue(s);
									pif.push_back(pair<string, int>(s, hashy.FindValue(s)));
									added_here = true;
								}
								
							}
						}
						else if (s == "0")
						{
							hashy.AddValue(s);
							pif.push_back(pair<string, int>(s, hashy.FindValue(s)));
							added_here = true;

						}
						else if (s[0] != '0')
						{
							bool okk = true;
							for (int j = 0; j < s.length(); j++)
							{
								if (s[j] == '0' || s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9')
									continue;
								okk = false;
								break;
							}
							if (okk == true)
							{
								hashy.AddValue(s);
								pif.push_back(pair<string, int>(s, hashy.FindValue(s)));
								added_here = true;
							}
						}

						if (added_here == false)
						{
							bool okkkk = true;
							int j = 0;
							if (s[j] == '0' || s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9')
								okkkk = false;

							if (okkkk == true)
							{
								hashy.AddValue(s);
								pif.push_back(pair<string, int>(s, hashy.FindValue(s)));
							}
						}
					}

				}


				pch = strtok(NULL, " ");
			}


		}
		myFile.close();

		for (int i = 0; i < pif.size(); i++)
		{
			cout << '\t' << pif[i].first << '\t' << pif[i].second << '\n';

		}

	}
	else cout << "Unable to open file";


	_getch();
	return 0;
}