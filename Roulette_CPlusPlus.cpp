#include "stdafx.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <unordered_map>
using namespace std;


void roulette()
{
	while(true)
	{
		srand(time(0));
		int rnd = (rand()%2);
		int seq = 1;
		int prevRnd = -1;
		int max = 10000000;
		vector<int> seqs(max,0);
		cout << "Simulating " << max << " rounds" << endl;
		clock_t start = clock();

		for (int i = 0; i < max; i++)
		{
			prevRnd = rnd;
			rnd = (rand()%2);

			if (rnd == prevRnd) seq++;
			else
			{
				seqs[seq]++;
				seq = 1;
			}
		}
		cout << "Time: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;

		for (int i = 0; i < max; i++)
		{
			if(seqs[i] != 0) cout << seqs[i] << "\t" << i << endl; 
		}

		int a;
		cin >> a;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	roulette();
	return 0;
}
