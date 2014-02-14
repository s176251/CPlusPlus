/*
	C++ 2014, Oblig 1, Nøtt-oppgave. Av Martin W. Løkkeberg(s176251). (C++98). 
	
	Kommentarer:
	Stod at man skulle ha støtte for alle tegn fom. 32 tom. 96, men det blir jo 65 tegn som vil kreve 7 bit,
	eller evt. 6 bit om man eksluderer tegn 32 eller 96, men 5 bit holder jo kun til 32 tegn. Antar derfor
	at jeg enten har misforstått oppgaven eller at det står feil, at det skulle vært 6 bit.

	Jeg har iallefall valgt å tolke oppgave slik at man tar imot en string og returnerer
	et char array hvor hvert originale tegn nå tar 6 bit istedenfor 8, man får da altså
	inn 4 tegn på 3 byte, 8 på 6, 16 på 12, osv.
	
	Har endret noe på metodesignaturene siden antall byte er avhengig av antall chars i stringen,
	og jeg trenger derfor ingen parameter for denne.
	Det jeg dog trengte var en int som settes til antall byte i retur-arrayet, da dette i visse tilfeller vil kunne ha
	en null-char på en vilkårlig plass, så iterering med "while(*ptr)" vil ikke funke.
	Var også nødt til å bruke unsigned char da signed char oppfører seg annerledes ved bit shifting. 

*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

string decompress(unsigned char* ptr, int length)
{	
	string str;
	unsigned char temp = '\0';
	unsigned char curr = '\0';
	unsigned char twoBits = (unsigned char)3;
	unsigned char fourBits = (unsigned char)15;
	unsigned char sixBits = (unsigned char)63;
	int i = 0;
	unsigned char* itr = ptr;
	
	while(i < length)
	{
		if( i%3 == 0 )	// add 6 + 2 bits
		{
			curr = *itr >> 2;			// Get the 6 leftmost bits and move them right. xxxx xxyy -> 00xx xxxx.
			str += (unsigned char)(curr + 31);	// 
			temp = *itr & twoBits; 		// Make sure to only get the two rightmost bits xxxx xxyy & 0000 0011 -> 0000 00yy.
			temp = temp << 4;			// Make sure they're in the right spot, 0000 00yy -> 00yy 0000, for the next iteration.
		}
		else if( i%3 == 1 ) //add 4 + 4 bits
		{ 
			curr = *itr >> 4;			// Get the 4 leftmost bits and move them right, yyyy zzzz -> 0000 yyyy.
			curr = curr | temp;			// Combine the current bits and 2 bits form the last iteration, 00yy 0000 | 0000 yyyy -> 00yy yyyy.
			str += (unsigned char)(curr + 31);	//
			temp = *itr & fourBits;		// Make sure to only get the four rightmost bits, xxxx xxyy & 0000 1111 -> 0000 zzzz.
			temp = temp << 2;			// Make sure they're in the right spot, 0000 zzzz -> 00zz zz00, for the next iteration.
		}
		else if( i%3 == 2 )	// add 2 + 6 bits
		{	
			curr = *itr >> 6;			// Get the 2 leftmost bits and move them right. zzcc cccc -> 0000 00zz.
			curr = curr | temp;			// Combine the current bits and 4 bits form the last iteration, 0000 00zz | 00zz zz00 -> 00zz zzzz.			
			str += (unsigned char)(curr + 31);
			curr = *itr & sixBits;		// Make sure to only get the six rightmost bits xxcc cccc & 0011 1111 -> 00cc cccc.
			unsigned char tmp = (unsigned char)(curr + 31);
			if( ((int)tmp) > 31) str += tmp;
		}
		itr++;
		i++;
	}
	return *(new string(str));
}

unsigned char* compress(string s, int* arrLength)
{ 
	// 32		 ->        94 // Gyldig input er tegn med ascii verdi fom 32 tom 94 (totalt 63 tegn, kan representeres med 6 bit)
	// 0010 0000 -> 0101 1110
	// -31					  // Trekker ifra 31 slik at tegnene går fom. 1 tom 63., lar 0 være 0 slik at den fortsatt vil fungere som "end-of-string" markør. (har innsett at nei det funker ikke, men lar 31 stå).
	// 0000 0000 -> 0011 1111
	float f = (s.size()*6.0) / 8.0;  // Finn antall bytes som trengs med 6 bits tegn.
	int bytesNeeded = ceil(f);	
	(*arrLength) = bytesNeeded;
	unsigned char* result = (unsigned char*)malloc((sizeof(unsigned char) * bytesNeeded));
	int charsAdded = 0;
	int totalChars = s.size();
	int currentChar = 0;
	unsigned char temp = '\0';
	
	for(int i = 0; i < bytesNeeded; i++)
	{
		unsigned char curr = ((unsigned char)((toupper(s.at(currentChar++))-31))) & ((unsigned char)63); // Konverter små til store bokstaver og "klipper" tegn med ascii verdi over 63.
		charsAdded++;
				
		if( i%3 == 0 )	// add 6 + 2 bits
		{	
			result[i] = curr << 2;
			if(charsAdded != totalChars)
			{
				curr = (unsigned char)toupper((toupper(s.at(currentChar))-31)) & ((unsigned char)63);
				temp = curr >> 4;
				result[i] = result[i] | temp;
			}
		}
		else if( i%3 == 1 ) //add 4 + 4 bits
		{
			result[i] = curr << 4;
			if(charsAdded != totalChars)
			{
				curr = (unsigned char)toupper((toupper(s.at(currentChar))-31)) & ((unsigned char)63);
				temp = curr >> 2;
				result[i] = result[i] | temp;
			}			
		}
		else if( i%3 == 2 )	// add 2 + 6 bits
		{
			result[i] = curr << 6;
			if(charsAdded != totalChars)
			{
				curr = (unsigned char)toupper((toupper(s.at(currentChar++))-31)) & ((unsigned char)63);
				result[i] = result[i] | curr;
				charsAdded++;
			}			
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	string text = "HEISANN! Hvordan har du det i dag?";
	cout << endl << "Tekst pre-komprimering: \"" << text << "\"" << endl << text.size() << " bytes" << endl << endl ;
	
	int l;
	unsigned char* compressedText = compress(text, &l);
	cout << "Komprimert tekst:       \"";
	for(int i = 0; i < l; i++)
	{
		cout << compressedText[i];
	}
	string decompressedText = decompress(compressedText, l);
	cout << "\"" << endl << l << " bytes" << endl << endl << "Dekomprimert tekst:     \"" << decompressedText << "\"" << endl;
	
	return 0;
}




















