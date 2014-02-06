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

#define INIT_CAP 100 //MUST BE > 1 
int* const added = (int*)malloc(sizeof(int*));
int* const current_array_size = (int*)malloc(sizeof(int*));

struct word_freq {
	string* word;
	int* freq;
};

// Used to sort the word_freq by frequency.
bool sortByFreq(const word_freq &l, const word_freq &r) { return *(l.freq) > *(r.freq); }

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

int compareFreq(const void* p1, const void* p2) 
{
	const word_freq* one = (const word_freq*)p1;
	const word_freq* two = (const word_freq*)p2;
	
	if(one->freq > 0 ) cout << *(one->freq) << " : ";
	
	cout << one->freq << endl;
	//if( *(one->freq) > *(two->freq) ) return 1;
	//if( *(one->freq) < *(two->freq) ) return -1;
	return 0;
  //const int f1 = *(((const word_freq*)p1)->freq);
  //const int f2 = *(((const word_freq*)p2)->freq);
  //if (f1 == f2) return 0;
  //return (f1 > f2) ? 1 : -1;
}

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
	string inputWord; 			 // temp-variable for pipeline input.
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
	/*
	for( int i = 0; i < *added; i++)
	{
		cout << *(wc[i]->word) << ":" << *(wc[i]->freq) << endl;
	}*/	

	// If argument passed, print the n most frequent words.
	if( argc > 1)
	{
		int  n = atoi(argv[1]);
		
		//Sort by frequency
		inefficientSort(wc, *added);
		
		// Print sorted on frequency
		for(int i = 0; i < *added; i++)
		{
			if( i > n) break;
			cout << *(wc[i]->word) << ":" << *(wc[i]->freq) << endl;
		}	
	}
	
	for( int i = 0; i < *added; i++)
	{
		delete wc[i]->word;
		delete wc[i]->freq;
		delete wc[i];
	}	
	free(wc);	
	
	return 0;
}
