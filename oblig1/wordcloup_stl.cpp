#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "./stop.h"

using namespace std;

string legalizeString(string* strp)
{
	string str;
	int a = strp->length();
	bool skip = false;

	for (int i = 0; i < a; i++)
	{
		char* ptr = (char*)stopchars_c;
		while(*ptr)
		{
			if((*strp)[i] == *ptr)
			{
				skip = true;
				break;
			}
			ptr++;
		}

		if(!skip)
		{
			str += tolower((*strp)[i]);
		}
		else
			skip = false;
	}
	return str;
}

string legalizeString2(string* strp)
{
	int a = strp->length();

	for (int i = strp->length(); i > 0; i--)
	{
		char* ptr = (char*)stopchars_c;
		while(*ptr)
		{
			if((*strp)[i] == *ptr)
			{
				strp->erase(i, 1);
			}
			else
			{
				strp->replace(i,1,1,(char)tolower((*strp)[i]));
			}
			ptr++;
		}
	}
	return *strp;
}

int main(int argc, char* argv[])
{
	//vector <int> counts;
	//vector <string> words;
	std::map<std::string, int> wordCount;
	std::map<std::string, int> ignore;
	string line;
	string word;
	//getline(cin, a)
	char* ptr = (char*)stopwords_c;
	string str;

	while(*ptr)
	{
		if(*ptr == ',')
		{
			ignore[str]++;
			str.clear();
		}
		else
		{
			str += *ptr;
		}
		ptr++;
	}

	while(cin >> word)
	{
		word = legalizeString2(&word);
		if(ignore.count(word) == 0)
			wordCount[word]++;
	}

	for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); it++)
	{
		cout << it->first <<" : "<< it->second << endl;
	}
	
	return 0;
}
