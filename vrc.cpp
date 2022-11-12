// VRC
// Author: Jitin
#include <bits/stdc++.h>
using namespace std;
// parity generator
// 0111 0110 1110
// 0111 0110 1110 101
string vrc(string data)
{
	// for every 4 characters in the string if number of 1s is odd append 1 else append 0
	int n = data.length();
	for (int i = 0; i < n; i += 4)
	{
		string temp = data.substr(i, 4);
		int count_1 = 0;
		for (int j = 0; j < temp.length(); j++)
		{
			if (temp[j] == '1')
				count_1++;
		}
		if (count_1 % 2 == 0)
			data.append("0");
		else
			data.append("1");
		// cout << count(data.substr(i, 4).begin(), data.substr(i, 4).end(), '1') << endl;
		// count(data.substr(i, 4).begin(), data.substr(i, 4).end(), '1') % 2 == 1 ? data.append("1") : data.append("0");
	}
	cout << "vrc: " << data << endl;
	return data;
}

// receiver side checker
bool check(string data)
{
	int x = data.size();
	int extra_bits = x / 4;
	int par_start = x - extra_bits;
	// for every 4 characters in the string if number of 1s is odd return false else return true
	for (int i = 0; i < x - extra_bits; i += 4)
	{
		string temp = data.substr(i, 4);
		int count_1 = 0;
		for (int j = 0; j < temp.length(); j++)
		{
			if (temp[j] == '1')
				count_1++;
		}
		// cout << "count_1: " << count_1 << endl;
		if (count_1 % 2 == 1 && data[par_start + i / 4] == '0')
			return false;
		else if (count_1 % 2 == 0 && data[par_start + i / 4] == '1')
			return false;
	}
	return true;
}
int main()
{
	string data;
	cout << "Enter data: ";
	cin >> data;
	// If data is not multiple of 4 append 0s to the start of the string
	int x = data.size();
	if (x % 4 != 0)
	{
		int extra_bits = 4 - x % 4;
		for (int i = 0; i < extra_bits; i++)
		{
			data.insert(0, "0");
		}
	}
	// print data with spaces after every 4 characters
	cout << "After padding: ";
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i];
		if (i % 4 == 3)
			cout << " ";
	}
	cout << endl;
	vrc(data);
	string receiver_data;
	cout << "Enter receiver data: ";
	cin >> receiver_data;
	if (check(receiver_data))
		cout << "Data is valid" << endl;
	else
		cout << "Data is invalid" << endl;
	return 0;
}