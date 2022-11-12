// Hamming code
// Author: Jitin (CS201075)
// Corrects single bit errors
#include <bits/stdc++.h>
using namespace std;

// integer to binary in n bits
string int_to_bin(int n, int bits)
{
	string bin = "";
	while (n > 0)
	{
		bin = to_string(n % 2) + bin;
		n /= 2;
	}
	while (bin.length() < bits)
		bin = "0" + bin;
	return bin;
}

// binary to integer
int bin_to_int(string bin)
{
	int n = 0;
	for (int i = 0; i < bin.length(); i++)
		n += (bin[i] - '0') * pow(2, bin.length() - i - 1);
	return n;
}
// parity finder
int parity_finder(int parity, int n, vector<int> hamming, int r)
{
	int ans = 0;
	// cout << "Considered positions are\n";
	for (int i = 1; i <= n; i++)
	{
		string position_in_binary = int_to_bin(i, r);
		int size = position_in_binary.size();
		if (position_in_binary[size - parity - 1] == '1') // consider this position;
		{
			// cout << i << " ";
			ans = ans ^ hamming[i];
		}
	}
	return ans;
}

// Generate hamming code function
void hamming_code()
{
	string msg;
	cout << "Enter message\n";
	cin >> msg;
	int m = msg.size();
	int r = 1;
	int i;
	while (1 << r < m + r + 1)
	{
		r++;
	}
	cout << "m=" << m << " r=" << r << endl;
	int msg_ptr = 0;
	vector<int> hamming(m + r + 1, 0);
	for (int i = m + r; i > 0; i--)
	{
		if (floor(log2(i)) == log2(i))
		{
			continue; //redundant bit
		}
		else
		{
			hamming[i] = int(msg[msg_ptr++] - 48); //copy from receiver msg to hamming code
		}
	}
	// Filling parity bits
	for (int i = 0; i < r; i++)
	{
		hamming[1 << i] = parity_finder(i, m + r, hamming, r);
		cout << "hamming[" << (1 << i) << "]=" << hamming[1 << i] << endl;
	}

	cout << "The hamming code is:\n";
	reverse(hamming.begin(), hamming.end());
	hamming.pop_back();
	for (int i = 0; i < m + r; i++)
	{
		cout << hamming[i];
	}
	cout << endl;
}

// Checking from receiver side
void check_hamming_code()
{
	string hamming;
	cout << "Enter the hamming code received\n";
	cin >> hamming;
	int r = ceil(log2(hamming.size()));
	int m = hamming.size() - r;
	reverse(hamming.begin(), hamming.end());
	vector<int> h(m + r + 1);
	for (int i = 1; i <= m + r; i++)
	{
		h[i] = hamming[i - 1];
	}

	int i = 0;
	for (i = 0; i < r; i++)
	{
		if (parity_finder(i, m + r, h, r) == 0)
			continue;
		else
		{
			cout << "Incorrect\n";
			break;
		}
	}
	if (i == r)
	{
		cout << "Correct\n";
		return;
	}
	// Correcting the error
	string correct_parity;
	cout << "The error bit position is\n";
	for (i = 0; i < r; i++)
	{
		if (parity_finder(i, m + r, h, r) == 0)
			correct_parity += '0';
		else
			correct_parity += '1';
	}
	reverse(correct_parity.begin(), correct_parity.end());
	cout << m + r - bin_to_int(correct_parity) + 1;
}
int main()
{
	hamming_code();
	check_hamming_code();
	return 0;
}