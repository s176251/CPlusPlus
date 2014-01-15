#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int words = 0;
	string a;
	bool firstNonSpace;

	while(getline(cin, a))
	{
		firstNonSpace = true;
		for (int i = 0; i < a.length(); i++)
		{
			if(a[i] != ' ' && firstNonSpace)
			{
				words++;
				firstNonSpace = false;
			}
			else if(a[i] == ' ')
			{
				firstNonSpace = true;
			}
		}
	}
	cout << words << endl;
	return words;
}
