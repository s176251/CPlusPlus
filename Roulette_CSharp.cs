using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Roulette
{
	class RouletteSimulation
	{
		static void Main(string[] args)
		{
			rouletteArray();
			//rouletteDictionary();
		}

		static void rouletteDictionary()
		{
			while (true)
			{
				Console.Write("Enter rounds(q to quit): ");
				string input = Console.ReadLine();
				if (input == "q" || input == "quit" || input == "Get me the hell out!!!") break;

				int max = 0;
				try
				{
					max = Convert.ToInt32(input);
				}
				catch
				{
					max = 10000000;
				}
				Random rng = new Random();
				int rnd = rng.Next(0, 2);

				int seq = 1;

				int prevRnd = -1;

				Dictionary<int, int> seqs = new Dictionary<int, int>();

				Console.WriteLine("Simulating " + max.ToString("#,##0") + " rounds of roulette.");

				DateTime begin = DateTime.UtcNow; // Start timing

				for (int i = 0; i < max; i++)
				{
					prevRnd = rnd;
					rnd = rng.Next(0, 2);

					if (rnd == prevRnd) seq++;
					else
					{
						if (seqs.ContainsKey(seq)) seqs[seq]++;				
						else seqs[seq] = 1;									

						seq = 1;
					}
				}
				DateTime end = DateTime.UtcNow; // Stopp timing
				Console.WriteLine("Measured time: " + (end - begin).TotalMilliseconds + " ms.");

				foreach (var s in seqs)
				{
					Console.WriteLine(s.Key + "\t" + s.Value);
				}
			}
		}


		static void rouletteArray()
		{
			while (true)
			{
				Console.Write("Enter rounds(q to quit): ");
				string input = Console.ReadLine();
				if (input == "q" || input == "quit" || input == "Get me the hell out!!!") break;

				int max = 0;
				try
				{
					max = Convert.ToInt32(input);
				}
				catch
				{
					max = 10000000;
				}
				Random rng = new Random();
				int rnd = rng.Next(0, 2);

				int seq = 1;

				int prevRnd = -1;

				int[] seqs = new int[max];			

				Console.WriteLine("Simulating " + max.ToString("#,##0") + " rounds of roulette.");

				DateTime begin = DateTime.UtcNow; // Start timing

				for (int i = 0; i < max; i++)
				{
					prevRnd = rnd;
					rnd = rng.Next(0, 2);

					if (rnd == prevRnd) seq++;
					else
					{
						seqs[seq]++;

						seq = 1;
					}
				}
				DateTime end = DateTime.UtcNow; // Stopp timing
				Console.WriteLine("Measured time: " + (end - begin).TotalMilliseconds + " ms.");

				for (int i = 0; i < seqs.Length; i++)
				{
					if (seqs[i] != 0) Console.WriteLine(i + "\t" + seqs[i]);
				}
			}
		}
	}
}
