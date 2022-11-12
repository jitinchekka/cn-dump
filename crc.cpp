#include <iostream>
using namespace std;
// cyclic redundancy check
string crc(string datablock, string divisor)
{
	string temp;
	string quotient;
	string dividend = datablock;
	// append n-1 zeros to the dividend
	for (int i = 0; i < divisor.length() - 1; i++)
	{
		dividend = dividend + '0';
	}
	// modulo 2 division
	int n = dividend.length() - divisor.length() + 1;
	temp = dividend.substr(0, divisor.length());
	for (int i = 0; i < n; i++)
	{
		if (dividend[i] == '1')
		{
			
		}
		else
		{
			remainder = remainder + '0';
		}
	}
}
int main()
{
	return 0;
}