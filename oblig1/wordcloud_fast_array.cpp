// 2014-02-14 - Martin W. Løkkeberg (s176251) - C++98.
// Counts word frequency from pipeline, uses an array of structs with int and string.
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

#define INIT_CAP 600 //MUST BE > 1                          // Determines initial amount reserved for words.
int* const added = (int*)malloc(sizeof(int*));              // Keeps track of added words.
int* const current_array_size = (int*)malloc(sizeof(int*)); // Keeps track of the number of indeces in the array.

struct word_freq {
	string word;
	int freq;
};

// Returns the index of the word in array or -1 if not present.
int isWordInArray(word_freq** words, string word)
{
	for( int i = 0; i < *added; i++)
	{
		if((words[i]->word).compare(word) == 0)
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
			a = words[i]->freq;
			b = words[i+1]->freq;

			if(a < b)
			{
				word_freq* tmp = words[i];
				words[i] = words[i+1];
				words[i+1] = tmp;
			}
		}
}

// Returns false if word is in ignore-list
bool includeWord(string** arr, int n, string word)
{
	for( int i = 0; i < n; i++)
	{
		if((arr[i])->compare(word) == 0)
		{
			return false;
		}
	}
	return true;
}

//Entry point. Reads text from pipe and counts words.
int main(int argc, char* argv[])
{
	// Create list of words to ignore
		int ignoreWords = 119; //Her har jeg juksa litt og satt denne på forhånd, men passer på å reallokere hvis den skulle endre seg.
		string** ignore = (string**)malloc(ignoreWords * sizeof(string*));
		char* ptr = (char*)stopwords_c;
		string str;
		int wordsAdded = 0;
		while(*ptr)
		{
			if(wordsAdded >= ignoreWords)
			{
				ignore = (string**)realloc(ignore, ++ignoreWords * sizeof(string*));
			}

			if(*ptr == ',')
			{
				ignore[wordsAdded++] = new string(str);
				str.clear();
			}
			else
			{
				str += *ptr;
			}
			ptr++;
		}

	// Create word<->frequency array.
		word_freq** wc = (word_freq**)malloc(INIT_CAP * sizeof(word_freq*));
		*current_array_size = INIT_CAP;
		*added = 0;
	
	//Read from pipeline and add to word<->frequency array.
		int index = -1;
		string inputWord;
		while(cin >> inputWord)
		{
			inputWord = legalizeString(&inputWord);

			if((inputWord.length() > 0) && (includeWord(ignore, ignoreWords, inputWord)))
			{
				index = isWordInArray(wc, inputWord);

				if(index != -1)
				{
					(wc[index]->freq)++;
				}
				else
				{
					wc[*added] = new word_freq;
					wc[*added]->word = inputWord;
					wc[*added]->freq = 1;
					(*added)++;
					if( *added == *current_array_size) // Reallocate array memory if words keep pouring in.
					{
						*current_array_size += ((*added)/2);
						wc = (word_freq**)realloc(wc, (*current_array_size) * sizeof(word_freq*));
					}					
				}
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
				printf("%20s : %d \n", (wc[i]->word).c_str(), wc[i]->freq);
			}
		}

	// Clean house
		for( int i = 0; i < *added; i++)
		{
			delete wc[i];
		}
		free(wc);
		free(added);
		free(current_array_size);
		for( int i = 0; i < ignoreWords; i++)
		{
			delete ignore[i];
		}
		free(ignore);
		
	return 0;
}
