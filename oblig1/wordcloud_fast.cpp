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

#define INIT_CAP 600 //MUST BE > 1
int* const added = (int*)malloc(sizeof(int*));
int* const current_array_size = (int*)malloc(sizeof(int*));

struct word_freq {
	string* word;
	int* freq;
};

// Returns the index of the word in array or -1 if not present.
int isWordInArray(word_freq** words, string word)
{
	for( int i = 0; i < *added; i++)
	{
		if((words[i]->word)->compare(word) == 0)
		{
			return i;
		}
	}
	return -1;
}

// n^2 descending sort by frequency.
void inefficientSort(word_freq** words, int n)
{
	int a = 0;
	int b = 0;

	for( int j = 0; j < n-1; j++)
		for( int i = 0; i < n-1; i++)
		{
			a = *(words[i]->freq);
			b = *(words[i+1]->freq);

			if(a < b)
			{
				word_freq* tmp = words[i];
				words[i] = words[i+1];
				words[i+1] = tmp;
			}
		}
}

//Entry point. Reads text from pipe and counts words.
int main(int argc, char* argv[])
{
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

	word_freq **wc;
	wc = (word_freq**)malloc(INIT_CAP * sizeof(word_freq*));

	*current_array_size = INIT_CAP;
	*added = 0;
	int index = -1;
	string inputWord;

	//Read from pipeline
	while(cin >> inputWord)
	{
		//Remove illegal chars and convert to lowercase.
		inputWord = legalizeString(&inputWord);

		if((inputWord.length() > 0) && (ignore.count(inputWord) == 0))
		{
			index = isWordInArray(wc, inputWord);

			if(index != -1)
			{
				(*(wc[index]->freq))++;
			}
			else
			{
				wc[*added] = new word_freq;
				wc[*added]->word = new string(inputWord);
				wc[*added]->freq = new int(1);
				(*added)++;
			}
		}
		if( *added == *current_array_size)
		{
			*current_array_size += ((*added)/2);
			wc = (word_freq**)realloc(wc, (*current_array_size) * sizeof(word_freq*));
		}
	}

	// If argument passed, print the n most frequent words.
	if( argc > 1)
	{
		int  n = atoi(argv[1]);

		//Sort by frequency
		inefficientSort(wc, *added);

		// Print sorted on frequency
		for(int i = 0; i < *added; i++)
		{
			if( i >= n) break;
			printf("%20s : %d \n", (wc[i]->word)->c_str(), *(wc[i]->freq));
		}
	}

	for( int i = 0; i < *added; i++)
	{
		delete wc[i]->word;
		delete wc[i]->freq;
		delete wc[i];
	}
	free(wc);
	free(added);
	free(current_array_size);
	return 0;
}
