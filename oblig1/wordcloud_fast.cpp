#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "./stop.h"
#include <utility>
#include <stdio.h>
using namespace std;

// Removes illegal chars defined in stop.h, and converts to lowercase.
string legalizeString(string* strp)
{
	string str;
	str.reserve(strp->size()); //The new string is likely the same size.
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


// Used to sort the word,frequency pairs by frequency.
bool sortByFreq(const pair<string, int> &l, const pair<string, int> &r) { return l.second > r.second; }

#define INIT_CAP 500

struct word_freq {
	char* word;
	int freq;
};


//Entry point. Reads text from pipe and counts words.
int main(int argc, char* argv[])
{
	word_freq **wc;
	wc = (word_freq**)malloc(INIT_CAP * sizeof(word_freq*));
	
	free(wc);

	/*
	//Create map of ignore words.
	std::map<std::string, int> ignore;
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

	map<std::string, int> wordCount; // Map to store words and their frequency.
	string word; 			 // temp-variable for pipeline input.


	
	//Read from pipeline
	while(cin >> word)
	{
		//Remove illegal chars and convert to lowercase.
		word = legalizeString(&word);

		//Add to map if not present in ignore-list
		if(ignore.count(word) == 0)
			wordCount[word]++;
	} */

	// If argument passed, print the n most frequent words.
	if( argc > 1)
	{
		/*
		int  n = atoi(argv[1]);

		//Sort the map by frequency into a vector of pairs
		vector< pair<string, int> > byFreq;
		for (map<string, int>::iterator itr  = wordCount.begin(); itr != wordCount.end(); itr++)
		{
			pair <string, int> tmp (itr->first, itr->second);
			byFreq.push_back(tmp);
		}
		sort(byFreq.begin(), byFreq.end(), sortByFreq);


		// Print sorted on frequency
		int i = 0;
		for ( vector< pair<string, int> >::iterator itr = byFreq.begin(); itr != byFreq.end(); itr++)
		{
			if(i++ >= n) break;
			printf("%20s : %d \n", itr->first.c_str(), itr->second);
			//cout << itr->first << " : " << itr->second << endl;
		} */
		// Print sorted on word
		/*for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); it++)
		{
			if(i++ >= n) break;
			cout << it->second <<" : "<< it->first << endl;
		}*/
	}
	return 0;
}
