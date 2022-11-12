// Check Sum
// Author: Jitin
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> addBinaryNumbers(vector<vector<int>> data)
{
	// 1001
	// 1001
	// ans = 0011
	// temp = 0001
	int m = data[0].size();
	vector<int> temp = data[0];
	vector<int> result;
	int carry = 0;
	for (int i = m - 1; i >= 0; i--)
	{
		int sum = carry;
		for (int j = 0; j < data.size(); j++)
		{
			sum += data[j][i];
		}
		result.push_back(sum % 2);
		carry = sum / 2;
	}
	reverse(result.begin(), result.end());
	//Finally if carry!=0 i.e carrry=1, add 1 to result
	if (carry)
	{
		vector<int> temp(m, 0);
		temp[m - 1] = 1; //000000....1
		carry = 0;
		// add temp to result in binary
		for (int i = m - 1; i >= 0; i--)
		{
			int sum = temp[i] + result[i] + carry;
			result[i] = sum % 2;
			carry = sum / 2;
		}
	}
	return result;
}

bool checkEqual(vector<int> data1, vector<int> data2)
{
	if (data1.size() != data2.size())
	{
		cout << "Not equal" << endl;
		return false;
	}
	for (int i = 0; i < data1.size(); i++)
	{
		if (data1[i] != data2[i])
		{
			// cout << "Not equal" << endl;
			return false;
		}
	}
	return true;
}
// calculate the ones complement of a binary number
vector<int> ones_complement(vector<int> data)
{
	for (auto &i : data)
	{
		i = i ^ 1;
	}
	return data;
}
int main()
{
	// vector<vector<int>> data = {{1, 0, 1, 0}, {0, 1, 0, 0}};
	vector<int> user_input_data;
	int n;
	cout << "Enter number of bits: ";
	cin >> n;
	cout << "Enter sender data: " << endl;
	string str_data;
	cin >> str_data;
	for (int i = 0; i < n; i++)
	{
		int x;
		// cin >> x;
		user_input_data.push_back(int(str_data[i]-48));
	}
	if (n % 4 != 0)
	{
		int temp = n % 4;
		for (int i = 0; i < 4 - temp; i++)
		{
			user_input_data.insert(user_input_data.begin(), 0);
		}
	}
	vector<vector<int>> data;
	// split user input data into chunks of 4 bits
	cout<<"Sender data: "<<endl;
	for (int i = 0; i < user_input_data.size(); i += 4)
	{
		vector<int> temp;
		for (int j = 0; j < 4; j++)
		{
			temp.push_back(user_input_data[i + j]);
		}
		data.push_back(temp);
	}
	// print data
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[0].size(); j++)
		{
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
	vector<int> sender_side = addBinaryNumbers(data);
	cout << "Sender side checksum\n";
	for (int i = 0; i < sender_side.size(); i++)
	{
		cout << sender_side[i] << " ";
	}
	cout << endl;

	vector<int> user_input_data2;
	cout << "Enter receiver data: " << endl;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		user_input_data2.push_back(x);
	}
	if (n % 4 != 0)
	{
		int temp = n % 4;
		for (int i = 0; i < 4 - temp; i++)
		{
			user_input_data2.insert(user_input_data2.begin(), 0);
		}
	}
	vector<vector<int>> data2;
	// split user input data into chunks of 4 bits
	for (int i = 0; i < user_input_data2.size(); i += 4)
	{
		vector<int> temp;
		for (int j = 0; j < 4; j++)
		{
			temp.push_back(user_input_data2[i + j]);
		}
		data2.push_back(temp);
	}
	// print data
	cout << "Receiver side data\n";
	for (int i = 0; i < data2.size(); i++)
	{
		for (int j = 0; j < data2[0].size(); j++)
		{
			cout << data2[i][j] << " ";
		}
		cout << endl;
	}

	vector<int> receiver_side = addBinaryNumbers(data2);
	cout << "Receiver side checksum\n";
	for (int i = 0; i < receiver_side.size(); i++)
	{
		cout << receiver_side[i];
	}
	cout << endl;
	if (checkEqual(sender_side, receiver_side))
	{
		cout << "Equal" << endl;
	}
	else
	{
		cout << "Not equal" << endl;
	}
	return 0;
}