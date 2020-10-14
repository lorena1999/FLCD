#include <iostream>
#include <conio.h>
#include "HashTable.h"
#include <cstring>
#include <string>
#include <string.h>

using namespace std;

int main()
{
	HashTable hashy;
	string key = "";

	cout << hashy.AddValue("a") << endl;
	cout << hashy.AddValue("abc") << endl;
	cout << hashy.AddValue("b") << endl;
	cout << hashy.AddValue("x") << endl;
	cout << hashy.AddValue("nr") << endl;
	cout << hashy.AddValue("i") << endl;
	cout << hashy.AddValue("start") << endl;
	cout << hashy.AddValue("stop") << endl << endl;

	cout << hashy.FindValue("a") << endl;
	cout << hashy.FindValue("abc") << endl;
	cout << hashy.FindValue("jkdsjfiosjfdoh") << endl;
	cout << hashy.FindValue("start");


	_getch();
	return 0;
}