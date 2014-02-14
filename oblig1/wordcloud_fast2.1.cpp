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

struct word_freq {
	string* word;
	int* freq;
	word_freq* next;
};

void addWordToList(word_freq* words, string newWord)
{
	word_freq* tmp = words;
	while(tmp->next)
	{
		if((tmp->word)->compare(newWord) == 0)
		{
			(*(tmp->freq))++;
			return;
		}
		tmp = tmp->next;
	}
	if((tmp->word)->compare(newWord) == 0)
	{
		(*(tmp->freq))++;
		return;
	}
	tmp->next = new word_freq;
	(tmp->next)->word = new string(newWord);
	(tmp->next)->freq = new int(1);
	(tmp->next)->next = 0;
	return;
}

void inefficientDescendingSort(word_freq* headPointer)
{
	string* tmpWord;
	int* tmpFreq;
	for(word_freq* index = headPointer->next; index->next != 0; index = index->next) 
	{
		for (word_freq* selection = index->next; selection != 0; selection = selection->next) 
		{
			if (*(index->freq) < *(selection->freq)) 
			{	
				tmpWord = index->word;
				tmpFreq = index->freq;
				index->word = selection->word;
				index->freq = selection->freq;
				selection->word = tmpWord;
				selection->freq = tmpFreq;
			}
		}
	}
}

// Returns false if word is in ignore-list
bool includeWord(word_freq* list, string word)
{
	for(word_freq* i = list->next; i; i = i->next)
	{
		if((i->word)->compare(word) == 0)
		{
			return false;
		}
	}
	return true;
}

//Entry point. Reads text from pipe and counts words.
int main(int argc, char* argv[])
{
	//Create list of ignore words.
		word_freq* ignore = new word_freq;
		ignore->next = 0;
		char* ptr = (char*)stopwords_c;
		string str;
		word_freq* current = ignore;
		while(*ptr)
		{
			if(*ptr == ',')
			{	
				current->next = new word_freq;
				current = current->next;
				current->word = new string(str);
				str.clear();
			}
			else
			{
				str += *ptr;
			}
			ptr++;
		}
		current->next = 0;
	
	//Create word<->frequency list
		word_freq* headPointer = new word_freq;
		headPointer->word = new string("W/F-List");
		headPointer->next = 0;
		
	//Read from pipeline and add to word<->frequency list
		string inputWord;
		while(cin >> inputWord)
		{
			//Remove illegal chars and convert to lowercase.
			inputWord = legalizeString(&inputWord);

			if((inputWord.length() > 0) && (includeWord(ignore, inputWord)))
			{
				addWordToList(headPointer, inputWord);
			}
		}
	// If argument passed, print the n most frequent words.
		if( argc > 1)
		{
			int n = atoi(argv[1]);

			//Sort by frequency
			inefficientDescendingSort(headPointer);
			
			// Print sorted on frequency
			int i = 0;		
			word_freq* tmp = headPointer->next;
			while(tmp)
			{
				if( i++ >= n) break;
				
				printf("%20s : %d \n", (tmp->word)->c_str(), *(tmp->freq));
				tmp = tmp->next;
			}
		}

	// Free memory
		word_freq* helper = headPointer->next;
		word_freq* tmp = 0;
		while(helper)
		{
			tmp = helper;
			helper = tmp->next;
			delete tmp->word;
			delete tmp->freq;
			delete tmp;
		}	
		delete headPointer;
		
		helper = ignore->next;
		tmp = 0;
		while(helper)
		{
			tmp = helper;
			helper = tmp->next;
			delete tmp->word;
			delete tmp;
		}	
		delete ignore;		

	return 0;
}
