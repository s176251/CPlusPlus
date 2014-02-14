// 2014-02-14 - Martin W. Løkkeberg (s176251) - C++98.
#include <string>
#include <iostream>

using namespace std;

unsigned long long string_to_ulong(std::string s)
{
	const char* c = s.c_str();
	unsigned long long* a = (unsigned long long*)c;
	return *a;
}

std::string longlong_to_string(long long ll)
{
	const char* c = (char*)&ll;
	string s(c,8);
	return s;
}

int main(int argc, char* argv[])
{
	unsigned long long longstr = string_to_ulong("I love C++");  // String to long long
	std::string strlong = longlong_to_string(longstr);           // long long to String
	cout << strlong << endl;
	return 0;
}
