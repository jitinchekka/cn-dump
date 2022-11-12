// Author: Jitin
#include <bits/stdc++.h>
using namespace std;

// Bit stuffing

void display(vector<int> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i] << " ";
	}
}

void BitsStuffing(vector<int> data, int n)
{

	int count = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (data[i] == 0)
		{
			for (int j = i + 1; j < i + 6; j++)
			{
				if (data[j] == 1)
				{
					count++;
				}
				else
				{
					break;
				}
			}
		}
		if (count == 5)
		{
			data.insert(data.begin() + i + 6, 0);
			count = 0;
		}
	}

	// cout << "Size = " << data.size() << endl;
	cout << "Bits sequence after bit stuffing" << endl;
	display(data);
}

// b. Character Count

void CharacterCount(vector<int> data, int frame)
{
	int size = data.size();
	int count = 0, n = 1;
	count = size + frame;
	count = count / frame;

	data.insert(data.begin(), count);

	for (int i = count; i < data.size(); i += count)
	{
		if (count < size - (n * count))
		{
			data.insert(data.begin() + i, count);
			n++;
		}
		else
		{
			data.insert(data.begin() + i, (size - (n * count) + n + 1));
			break;
		}
	}

	cout << "\nData with character count" << endl;
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i] << " ";
	}

	// Reciever's Side

	cout << "\nData after Deframing" << endl;
	for (int i = 0; i < data.size(); i++)
	{
		if (i % count != 0 || i == (data.size() - 1))
			cout << data[i] << " ";
	}
}

// c. Byte Stuffing

void ByteDeStuffing(string data, char f)
{
	data.erase(data.begin());
	data.erase(data.end() - 1);

	for (int i = 0; i < data.size(); i++)
	{
		if ((data[i] == f || data[i] == 'E'))
		{
			data.erase(data.begin() + i);
		}
	}
	cout << "Data after character Destuffing is: ";
	cout << endl;
	;
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i];
		cout << " ";
	}
	cout << endl;
}

void ByteStuffing(string data, char f)
{
	data.insert(data.begin(), f);
	data.insert(data.end(), f);

	for (int i = 0; i < data.size(); i++)
	{
		if ((i != 0) && (i != data.size() - 1))
		{
			if ((data[i] == f || data[i] == 'E'))
			{
				data.insert(data.begin() + i, 'E');
				i++;
			}
		}
	}

	cout << "Data after Byte Stuffing where 'E' is ESC character\n";

	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i] << " ";
	}
	cout << "\n";
	ByteDeStuffing(data, f);
}

int main()
{
	bool Menu = true;
	while (Menu)
	{
		char c;
		cout << "\nPress 1 for Bits Stuffing" << endl
			 << "Press 2 for Byte Stuffing" << endl
			 << "Press 3 for Character Count" << endl
			 << "Press 4 to Exit" << endl;
		cout << "Please enter your input\t";
		cin >> c;
		switch (c)
		{
		case '1':
		{
			cout << "\nBITS STUFFING\n"
				 << endl;

			int size;
			vector<int> Data;

			cout << "Enter no of bits in data part" << endl;
			cin >> size;

			cout << "Enter bits sequence (int type space separated) without stuffing" << endl;
			for (int i = 0; i < size; i++)
			{
				int temp;
				cin >> temp;
				Data.push_back(temp);
			}

			size = Data.size();

			BitsStuffing(Data, size);

			cout << "\nBITS STUFFING\n"
				 << endl;
		}
		break;

		case '2':
		{
			cout << "\nBYTE STUFFING\n"
				 << endl;

			string Data;
			char flag;

			cout << "Enter bits (string type) sequence without stuffing" << endl;
			cin >> Data;

			cout << "Enter the flag bit" << endl;
			cin >> flag;

			ByteStuffing(Data, flag);

			cout << "\nBYTE STUFFING\n"
				 << endl;
		}
		break;

		case '3':
		{
			cout << "\nCHARACTER COUNT\n"
				 << endl;

			int size, frame;
			vector<int> Data;

			cout << "Enter no of bits in data part" << endl;
			cin >> size;

			cout << "Enter bits sequence (int type space separated) without stuffing" << endl;
			for (int i = 0; i < size; i++)
			{
				int temp;
				cin >> temp;
				Data.push_back(temp);
			}

			cout << "Enter no of frames" << endl;
			cin >> frame;

			size = Data.size();

			CharacterCount(Data, frame);

			cout << "\nCHARACTER COUNT\n"
				 << endl;
		}
		break;

		case '4':
		{
			cout << "Exiting the program" << endl;
			exit(0);
		}
		break;

		default:
		{
			cout << "Wrong Input Try Again" << endl;
			exit(0);
			break;
		}
		}
	}
	return 0;
}