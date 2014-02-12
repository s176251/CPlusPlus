// Uses C++11 functions, compile with -std=c++0x
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "./stop.h"
#include <stdio.h>
using namespace std;

string legalizeString(string* strp)
{
	string str;
	str.reserve(strp->size());
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

bool sortByFreq(const pair<string, int> &l, const pair<string, int> &r) { return l.second > r.second; }

int main(int argc, char* argv[])
{
	std::unordered_map<std::string, int> ignore;
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

	unordered_map<std::string, int> wordCount;
	string word;

	while(cin >> word)
	{
		word = legalizeString(&word);

		if(ignore.count(word) == 0)
			wordCount[word]++;
	}

	if( argc > 1)
	{
		int  n = atoi(argv[1]);

		vector< pair<string, int> > byFreq;
		for (unordered_map<string, int>::iterator itr  = wordCount.begin(); itr != wordCount.end(); itr++)
		{
			pair <string, int> tmp (itr->first, itr->second);
			byFreq.push_back(tmp);
		}
		sort(byFreq.begin(), byFreq.end(), sortByFreq);

		int i = 0;
		for ( vector< pair<string, int> >::iterator itr = byFreq.begin(); itr != byFreq.end(); itr++)
		{
			if(i++ >= n) break;
			printf("%20s : %d \n", itr->first.c_str(), itr->second);
		}
	}
	return 0;
}