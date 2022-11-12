#include <iostream>
#include <bitset>
using namespace std;
int main()
{
	string ip;
	cout << "Enter the IP address: ";
	cin >> ip;
	// Find the position of the first dot
	int pos1 = ip.find('.');
	// Find the position of the second dot
	int pos2 = ip.find('.', pos1 + 1);
	// Find the position of the third dot
	int pos3 = ip.find('.', pos2 + 1);
	// Extract the first octet
	string octet1 = ip.substr(0, pos1);
	// Extract the second octet
	string octet2 = ip.substr(pos1 + 1, pos2 - pos1 - 1);
	// Extract the third octet
	string octet3 = ip.substr(pos2 + 1, pos3 - pos2 - 1);
	// Extract the fourth octet
	string octet4 = ip.substr(pos3 + 1);
	// Convert the octets to integers
	int ip1 = stoi(octet1);
	int ip2 = stoi(octet2);
	int ip3 = stoi(octet3);
	int ip4 = stoi(octet4);
	// IP address in binary
	bitset<8> ip1Binary(ip1);
	bitset<8> ip2Binary(ip2);
	bitset<8> ip3Binary(ip3);
	bitset<8> ip4Binary(ip4);
	// Display IP address in binary
	cout << "IP Address in binary: ";
	cout << ip1Binary << "." << ip2Binary << "." << ip3Binary << "." << ip4Binary << endl;
	if (ip2 > 255 || ip3 > 255 || ip4 > 255)
	{
		cout << "Invalid IP address";
		return 0;
	}
	if (ip2 < 0 || ip3 < 0 || ip4 < 0)
	{
		cout << "Invalid IP address";
		return 0;
	}
	// Check if the IP address is a class A address
	if (ip1 >= 1 && ip1 <= 126)
	{
		cout << "Class A address";
	}
	else if (ip1 >= 128 && ip1 <= 191)
	{
		cout << "Class B address";
	}
	else if (ip1 >= 192 && ip1 <= 223)
	{
		cout << "Class C address";
	}
	else if (ip1 >= 224 && ip1 <= 239)
	{
		cout << "Class D address";
	}
	else
	{
		cout << "Class E address";
	}
}