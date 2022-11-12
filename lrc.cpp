// Longitudinal redundancy check
// Author: Jitin
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> parity(vector<vector<int>> &data)
{
	// for each column in the matrix calculate the parity and append it to the end of the column
	int n = data.size();
	data.push_back(vector<int>());
	for (int i = 0; i < data[0].size(); i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
		{
			if (data[j][i] == 1)
				count++;
		}
		if (count % 2 == 0)
			data[n].push_back(0);
		else
			data[n].push_back(1);
	}
	return data;
}

// print column wise -- for testing
void print(vector<vector<int>> data)
{
	cout << "Sent data: " << endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[0].size(); j++)
		{
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

// receiver side checker
bool check(vector<vector<int>> data)
{
	int n = data.size() - 1;
	for (int i = 0; i < data[0].size(); i++)
	{
		int count = 0;
		for (int j = 0; j < n; j++)
		{
			if (data[j][i] == 1)
				count++;
		}
		if (count % 2 == 1 && data[n][i] == 0)
			return false;
		else if (count % 2 == 0 && data[n][i] == 1)
			return false;
	}
	return true;
}
int main()
{
	vector<vector<int>> data;
	cout << "Enter the number of bits: ";
	int n;
	cin >> n;
	int rows = n / 4;
	int extra_bits = n % 4;
	cout << "Enter the data with spaces: " << endl;
	for (int i = 0; i < rows; i++)
	{
		vector<int> temp;
		for (int j = 0; j < 4; j++)
		{
			int x;
			// cout<<"Enter bit "<<i*4+j+1<<": ";
			cin >> x;
			temp.push_back(x);
		}
		data.push_back(temp);
	}
	parity(data);
	print(data);
	// Take user input for receiver data
	vector<vector<int>> receiver_data;
	cout << "Enter receiver data with spaces: " << endl;
	for (int i = 0; i < data.size(); i++)
	{
		vector<int> temp;
		for (int j = 0; j < data[0].size(); j++)
		{
			int x;
			cin >> x;
			temp.push_back(x);
		}
		receiver_data.push_back(temp);
	}
	if (check(receiver_data))
		cout << "Data is valid" << endl;
	else
		cout << "Data is not valid" << endl;
	return 0;
}