#include <iostream>
#include <vector>
using namespace std;
// Go Back N
void goBackN(int N, vector<int> data)
{
	vector<int> client;
	int windowStart = 0, windowEnd = N - 1;
	int curr = 0, sent = N - 1;
	for (int i = 0; i < N; i++)
	{
		cout << "Sent bit" << i << endl;
		client.push_back(data[i]);
	}

	while (curr != data.size())
	{
		bool ack;
		cout << "Acknowledge bit " << curr << endl;
		cin >> ack;
		if (ack == true)
		{
			windowStart++;
			windowEnd++;
			curr++;
			sent++;
			if (sent < data.size())
			{
				cout << "Sent bit " << sent << endl;
				client.push_back(data[sent]);
			}
		}
		else
		{
			cout << "Ack not received\nwindowStart=" << windowStart << " windowEnd=" << windowEnd << endl;
			// curr = windowStart;
			for (int i = windowStart; i <= windowEnd; i++)
			{
				cout << "Sent bit" << i << endl;
				client.push_back(data[i]);
			}
			sent = windowEnd;
		}
	}
	for (auto x : client)
	{
		cout << x << " ";
	}
	cout << "End of program\n";
}
int main()
{
	int N;
	cout << "Enter N\n";
	cin >> N;
	cout << "Enter size of data\n";
	int n;
	cin >> n;
	vector<int> data(n);
	cout << "Enter the data\n";
	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
	}
	goBackN(N, data);
	return 0;
}