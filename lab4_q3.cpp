// Jitin
// CS20B1075
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#define pb push_back

bool receiver(int n)
{
	int choice;
	cout << " \n1)choose one if reciever received frame\n";
	cout << "2) choose two if reciever not received frame\n";
	cout << "Enter your choice : ";
	cin >> choice;
	if (choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void sender(vector<int> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << "\n------------ Frame " << i << " is sent ------------" << endl;
		if (receiver(v[i]) == true)
		{
			cout << "\n------------- Data is received --------------";
			int choice;
			cout << "\n1) choose 1 if sender received Acknowledgement\n";
			cout << "2) choose 2 if sender didn't received Acknowledgement\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				cout << "\n------------- Acknowledgement is received --------------\n";
				continue;
			}
			else
			{
				cout << "End Protocol (Lost Acknowledgement)";
				break;
			}
		}
		else
		{
			cout << "End Protocol (Lost Data)";
			break;
		}
	}
}

int main()
{
	int n, x, j, t_t;
	cout << "Enter the no of frames : ";
	cin >> n;
	vector<int> v;
	cout << "Enter the Data of frames entered : ";
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		v.push_back(x);
	}
	sender(v);
	return 0;
}