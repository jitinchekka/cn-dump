#include <bits/stdc++.h>
using namespace std;

// CRC
string datablock, divisor, dividend, original_msg;
int len_divisor, len_dividend; // for CRC Code

string XOR(string Dividend_XOR, string Divisor_XOR)
{
	int size = Divisor_XOR.length();
	string xor_string;
	for (int i = 1; i < size; i++)
	{
		if (Dividend_XOR[i] == Divisor_XOR[i])
		{
			xor_string = xor_string + '0';
		}
		else
		{
			xor_string = xor_string + '1';
		}
	}

	return xor_string;
}

string polynomial_div(string temp_divisor, string Dividend, int len_of_divisor, int len_of_dividend, char p) // polynamial division
{
	string temp_dividend = Dividend.substr(0, len_of_divisor);
	int i = len_of_divisor;

	string ofZeros;
	for (int i = 0; i < len_of_divisor; i++)
	{
		ofZeros = ofZeros + '0';
	}

	while (i < len_of_dividend)
	{
		if (temp_dividend[0] == '1')
		{
			temp_dividend = XOR(temp_dividend, temp_divisor) + Dividend[i];
		}
		else
		{
			temp_dividend = XOR(temp_dividend, ofZeros) + Dividend[i];
		}

		i++;
	}

	if (temp_dividend[0] == '1')
	{
		temp_dividend = XOR(temp_dividend, temp_divisor);
	}
	else
	{
		temp_dividend = XOR(temp_dividend, ofZeros);
	}

	if (p == '1')
	{
		if (temp_dividend != ofZeros)
		{
			cout << "remainder ---> " << temp_dividend << "\n => There is distorssion during transmission" << endl;
		}
		else
		{
			cout << "remainder ---> " << temp_dividend << " \n=> No distorssion during transmission" << endl;
		}
	}
	return temp_dividend;
}

void getData(char p) // for input
{

	cout << "Enter databits that need to be transmitted" << endl;
	cin >> datablock;
	dividend = datablock;
	cout << "Enter divisor" << endl;
	cin >> divisor;

	len_divisor = divisor.length();
	int t = len_divisor - 1;
	for (int i = 0; i < t; i++)
	{
		dividend = dividend + '0';
	}
	// cout<<endl;

	len_dividend = dividend.length();

	// cout<<dividend<<endl;
	string remainder = polynomial_div(divisor, dividend, len_divisor, len_dividend, 0);
	original_msg = datablock + remainder;

	if (p == '0')
	{
		cout << endl;
		cout << "Results from sender side" << endl;
		cout << endl;
		cout << "Remainder on polynomial division from sender side is ---> " << remainder << endl; // call polynamial division
		cout << "Original message sent to reciever is --->" << original_msg << endl;
		// cout<<divisor<<endl;
	}
}

// VRC

void VRC()
{
	string finalans;
	string datapart;
	string appendbit;
	int divide = 4;
	cout << "Enter data bits that need to be transmitted" << endl;
	cin >> datapart;

	for (int i = 0; i < datapart.size(); i++)
	{
		if (datapart[i] != '0' && datapart[i] != '1')
		{
			cout << "ERROR  enter binary input" << endl;
			exit(0);
		}
	}

	for (int i = 0; i < datapart.size(); i += 4)
	{
		int count1 = 0;
		string temp = datapart.substr(i, divide);
		for (int j = 0; j < temp.size(); j++)
		{
			if (temp[j] == '1')
			{
				count1++;
			}
		}
		if (count1 % 2 == 1)
		{
			appendbit.push_back('1');
		}
		else
		{
			appendbit.push_back('0');
		}
	}

	finalans = appendbit + datapart;

	cout << "\nReciever end" << endl;
	cout << "Data transmitted from senders end : " << finalans << endl;

	string Final;
	cout << "Enter data that is recieved by reciever ";
	cin >> Final;

	int countof1 = 0;
	for (int j = 0; j < Final.size(); j++)
	{
		if (Final[j] == '1')
		{
			countof1++;
		}
	}

	if (countof1 % 2 == 0)
	{
		cout << "\nNo error in transmission\n"
			 << endl;
	}

	else
	{
		cout << "\nError in transmission\n"
			 << endl;
	}
}

// LRC

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

void LRC()
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
}

// Check Sum

vector<int> addBinaryNumbers(vector<vector<int>> data)
{

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
	// print result
	reverse(result.begin(), result.end());
	if (carry)
	{
		vector<int> temp(m, 0);
		temp[m - 1] = 1;
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

// HAMMING CODE
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
			continue;
		}
		else
		{
			// cout << "i = " << i << endl;
			hamming[i] = int(msg[msg_ptr++] - 48);
			// cout << "hamming[i]=" << hamming[i] << endl;
		}
	}
	// cout << parity_finder(2, m + r, hamming, r) << endl;
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

// main

int main()
{
	bool Menu = true;
	while (Menu)
	{
		char c;
		cout << "\nPress 1 for Error detection using VRC" << endl
			 << "Press 2 for Error detection using LRC" << endl
			 << "Press 3 for Error detection using Check Sum" << endl
			 << "Press 4 for Error detection using CRC" << endl
			 << "Press 5 for Error detection using Hamming" << endl
			 << "Press 6 to exit" << endl;
		cout << "Please enter your input\t";
		cin >> c;
		switch (c)
		{
		case '1':
		{
			cout << "\n\tVRC\t\n"
				 << endl;
			VRC();
			cout << "\n\tEND OF VRC\t\n"
				 << endl;
		}
		break;

		case '2':
		{
			cout << "\n\tLRC\t\n"
				 << endl;
			LRC();
			cout << "\n\tEND OF LRC\t\n"
				 << endl;
		}
		break;

		case '3':
		{
			cout << "\n\tCheck Sum\t\n"
				 << endl;
			vector<int> user_input_data;
			int n;
			cout << "Enter number of bits: ";
			cin >> n;
			cout << "Enter databits that need to be transmitted (with spaces ex: 1 0 1 0 1)" << endl;
			for (int i = 0; i < n; i++)
			{
				int x;
				cin >> x;
				user_input_data.push_back(x);
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
			cout << "Sender data: " << endl;
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
			for (int i = 0; i < n + 4; i++)
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
			int k = 0;
			// cout<<"Test"<<endl;
			for (k = 0; k < receiver_side.size(); k++)
			{
				// cout<<"Test"<<endl;
				if (receiver_side[k] == 0)
				{
					cout << "Not equal: Error found" << endl;
					break;
				}
				else
				{
					continue;
				}
			}
			if (k == receiver_side.size())
			{
				cout << "Equal: No Error" << endl;
			}
			cout << "\n\tEND OF CHECK SUM\t\n"
				 << endl;
		}
		break;

		case '4':
		{
			cout << "\n\tCRC\t\n"
				 << endl;

			bool menu = true;
			char select;

			do // menu driven program
			{
				cout << endl
					 << "Press 1\t No transmission errors" << endl
					 << "      2\t Having transmission errors" << endl
					 << "      3\t To exit CRC program" << endl;
				cout << "Select your choice : ";
				cin >> select;
				switch (select)
				{
				case '1':
				{
					cout << endl;
					getData('0');
					// string Divisor = divisor;
					cout << endl;
					cout << "Results from reciever side" << endl;
					cout << endl;
					// cout<<divisor<<<<endl;
					// cout<<original_msg<<endl;
					polynomial_div(divisor, original_msg, divisor.length(), original_msg.length(), '1');
					break;
				}
				case '2':
				{
					string distorted_msg;
					cout << endl;
					getData('0');
					// string Divisor = divisor;
					cout << endl;
					cout << "Input message after distorssion" << endl;
					cin >> distorted_msg;
					polynomial_div(divisor, distorted_msg, divisor.length(), distorted_msg.length(), '1');
					break;
				}

				case '3':
				{
					cout << "Exiting the program" << endl;
					exit(0);
				}

				default:
					cout << "Check your input and try again" << endl;
					break;
				}
			} while (menu);

			cout << "\n\tEND OF CRC\t\n"
				 << endl;
		}
		break;

		case '5':
		{
			cout << "\n\tHamming\t\n"
				 << endl;
			hamming_code();
			check_hamming_code();
		}
		break;

		case '6':
		{
			cout << "Exiting the program" << endl;
			exit(0);
		}
		break;

		default:
			cout << "Incorrect input Try Again" << endl;
			break;
		}
	}
	return 0;
}