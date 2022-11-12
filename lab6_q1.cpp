// Write a program to identify the class of a given IP address. Prompt the user to enter an IP address, validate the IP address and identify its class. Convert the given IP address to binary; based on the IP address identify the class and display the output.
//	IP Address Class A:
//		First Octet: 1-126
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class B:
//		First Octet: 128-191
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class C:
//		First Octet: 192-223
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class D:
//		First Octet: 224-239
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class E:
//		First Octet: 240-255
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class Invalid:
//		First Octet: 0
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class Invalid:
//		First Octet: 127
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
//	IP Address Class Invalid:
//		First Octet: 255
//		Second Octet: 0-255
//		Third Octet: 0-255
//		Fourth Octet: 0-255
#include <iostream>
using namespace std;
// Integer to binary function
void intToBinary(int num, int binary[8]) {
	int i = 0;
	while (num > 0) {
		binary[i] = num % 2;
		num /= 2;
		i++;
	}
}
int main()
{
	int ip1, ip2, ip3, ip4;
	// cout << "Enter the IP address: ";
	// cin >> ip1 >> ip2 >> ip3 >> ip4;
	cout<<"Enter the IP address: ";
	string ip;
	cin>>ip;
	for (int i = 0; i < ip.length(); i++)
	{
		if (ip[i] == '.')
		{
			ip[i] = ' ';
		}
	}
	// Split ip address into 4 parts and store in ip1, ip2, ip3, ip4 using space as delimiter
	sscanf(ip.c_str(), "%d %d %d %d", &ip1, &ip2, &ip3, &ip4);
	// IP address in binary
	int ip1Binary[8]={0}, ip2Binary[8]={0}, ip3Binary[8]={0}, ip4Binary[8]={0};
	// Convert ip address to binary
	intToBinary(ip1, ip1Binary);
	intToBinary(ip2, ip2Binary);
	intToBinary(ip3, ip3Binary);
	intToBinary(ip4, ip4Binary);
	// Display IP address in binary
	cout << "IP Address in binary: ";
	for (int i = 7; i >= 0; i--) {
		cout << ip1Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--) {
		cout << ip2Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--) {
		cout << ip3Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--) {
		cout << ip4Binary[i];
	}
	cout << endl;
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
	if (ip1 >= 1 && ip1 <= 126)
	{
		cout << "IP Address Class A" << endl;
	}
	else if (ip1 >= 128 && ip1 <= 191)
	{
		cout << "IP Address Class B" << endl;
	}
	else if (ip1 >= 192 && ip1 <= 223)
	{
		cout << "IP Address Class C" << endl;
	}
	else if (ip1 >= 224 && ip1 <= 239)
	{
		cout << "IP Address Class D" << endl;
	}
	else if (ip1 >= 240 && ip1 <= 255)
	{
		cout << "IP Address Class E" << endl;
	}
	else
	{
		cout << "IP Address Class Invalid" << endl;
	}
	return 0;
}
