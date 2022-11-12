// Consider a big single network of any class. Create and calculate the following:

// 1.      Divide the network into subnets.

// 2.      Total number of IP addresses

// 3.      Total number of hosts.

// 4.      Range of IP Address

// 5.      Direct and Limited broadcast address.

// 6.      Routing Table (Subnet ID, Subnet Mask, and Interface)
#include <iostream>
#include <math.h>
using namespace std;
// Integer to binary function
void intToBinary(int num, int binary[8])
{
	int i = 0;
	while (num > 0)
	{
		binary[i] = num % 2;
		num /= 2;
		i++;
	}
}
// PrintIP function
void printIP(int ip1Binary[8], int ip2Binary[8], int ip3Binary[8], int ip4Binary[8])
{
	cout << "IP Address in binary: ";
	for (int i = 7; i >= 0; i--)
	{
		cout << ip1Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--)
	{
		cout << ip2Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--)
	{
		cout << ip3Binary[i];
	}
	cout << ".";
	for (int i = 7; i >= 0; i--)
	{
		cout << ip4Binary[i];
	}
	cout << endl;
}

int main()
{
	string ip;
	cout << "Enter the IP address: ";
	cin >> ip;
	cout << "Enter the number of subnets: ";
	int n;
	cin >> n;
	int ip1, ip2, ip3, ip4;
	for (int i = 0; i < ip.length(); i++)
	{
		if (ip[i] == '.')
		{
			ip[i] = ' ';
		}
	}
	sscanf(ip.c_str(), "%d %d %d %d", &ip1, &ip2, &ip3, &ip4);
	int ip1Binary[8] = {0}, ip2Binary[8] = {0}, ip3Binary[8] = {0}, ip4Binary[8] = {0};
	intToBinary(ip1, ip1Binary);
	intToBinary(ip2, ip2Binary);
	intToBinary(ip3, ip3Binary);
	intToBinary(ip4, ip4Binary);
	printIP(ip1Binary, ip2Binary, ip3Binary, ip4Binary);
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

	// Finding the number of bits required for subnetting
	int bits = log2(n);
	cout << "Number of bits required for subnetting: " << bits << endl;
	// Find the class of the IP address
	if (ip1 >= 0 && ip1 <= 127)
	{
		cout << "Class A" << endl;
		// Divide the network into subnets
		cout << "Subnets: " << n << endl;
		// Total number of IP addresses
		int totalIP = pow(2, 24 - n);
		cout << "Total number of IP addresses: " << totalIP << endl;
		// // Total number of hosts
		int totalHosts = totalIP - 2;
		cout << "Total number of hosts: " << totalHosts << endl;
		cout << "Subnet ID\t\tSubnet Mask\t\tInterface\t\tRange of IP addresses\t\tDirect Broadcast Address\t\tLimited Broadcast address" << endl;
		int subnetID = 0;
		string subnetMask = "255." + to_string((n - 1) << (8 - bits)) + ".0.0";
		int x = 0;
		for (int i = 0; i < n; i++)
		{
			subnetID = i << (8 - bits);
			cout << to_string(ip1) + "." + to_string(subnetID) + ".0.0\t\t";
			cout << subnetMask << "\t\t";
			cout << "Interface " << i + 1 << "\t\t";
			cout << to_string(ip1) + "." + to_string(subnetID) + ".0.1 - " + to_string(ip1) + "." + to_string(subnetID + (int)pow(2, (8 - bits)) - 1) + ".255.254"
				 << "\t\t";
			string direct_broadcast_add = to_string(ip1) + "." + to_string(subnetID + (int)pow(2, (8 - bits))-1) + ".255.255";
			cout << direct_broadcast_add << "\t\t";
			cout << "255.255.255.255";
			cout << endl;
		}
	}
	else if (ip1 >= 128 && ip1 <= 191)
	{
		cout << "Class B" << endl;
		// Divide the network into subnets
		cout << "Subnets: " << n << endl;
		// Total number of IP addresses
		int totalIP = pow(2, 16 - bits);
		cout << "Total number of IP addresses: " << totalIP << endl;
		// Total number of hosts
		int totalHosts = totalIP - 2;
		cout << "Total number of hosts: " << totalHosts << endl;
		cout << "Subnet ID\t\tSubnet Mask\t\tInterface\t\tRange of IP addresses\t\tDirect Broadcast Address\t\tLimited Broadcast address" << endl;
		int subnetID = 0;
		string subnetMask = "255.255." + to_string((n - 1) << (8 - bits)) + ".0";
		int x = 0;
		for (int i = 0; i < n; i++)
		{
			subnetID = i << (8 - bits);
			cout << to_string(ip1) + "." + to_string(ip2) + "." + to_string(subnetID) + ".0\t\t";
			cout << subnetMask << "\t\t";
			cout << "Interface " << i + 1 << "\t\t";
			cout << to_string(ip1) + "." + to_string(ip2) + "." + to_string(subnetID) + ".1 - " + to_string(ip1) + "." + to_string(ip2) + "." + to_string(subnetID + (int)pow(2, (8 - bits)) - 1) + ".254"
				 << "\t\t";
			string direct_broadcast_add = to_string(ip1) + "." + to_string(ip2) + "." + to_string(subnetID + (int)pow(2, (8 - bits))-1) + ".255";
			cout << direct_broadcast_add << "\t\t";
			cout << "255.255.255.255";
			cout << endl;
		}
	}
	else if (ip1 >= 192 && ip1 <= 223)
	{
		cout << "Class C" << endl;
		// Divide the network into subnets
		cout << "Subnets: " << n << endl;
		// Total number of IP addresses
		int totalIP = pow(2, 8 - bits);
		cout << "Total number of IP addresses: " << totalIP << endl;
		// Total number of hosts
		int totalHosts = totalIP - 2;
		cout << "Total number of hosts: " << totalHosts << endl;
		cout << "Subnet ID\t\tSubnet Mask\t\tInterface\t\tRange of IP addresses\t\tDirect Broadcast Address\t\tLimited Broadcast address" << endl;
		int subnetID = 0;
		string subnetMask = "255.255.255." + to_string((n - 1) << (8 - bits));
		int x = 0;
		for (int i = 0; i < n; i++)
		{
			subnetID = i << (8 - bits);
			cout << to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(subnetID) << "\t\t";
			cout << subnetMask << "\t\t";
			cout << "Interface " << i + 1 << "\t\t";
			cout << to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(subnetID + 1) + " - " + to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(subnetID + (int)pow(2, (8 - bits)) - 1)
				 << "\t\t";
			string direct_broadcast_add = to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(subnetID + (int)pow(2, (8 - bits))-1);
			cout << direct_broadcast_add << "\t\t";
			cout << "255.255.255.255";
			cout << endl;
		}
	}
	else if (ip1 >= 224 && ip1 <= 239)
	{
		cout << "Class D" << endl;
		cout << "subnetting is not possible for class D" << endl;
		cout << "Limited Broadcast Address is not applicable for Class D IP address";
	}
	else if (ip1 >= 240 && ip1 <= 255)
	{
		cout << "Class E" << endl;
		cout << "subnetting is not possible for class E" << endl;
		cout << "Limited Broadcast Address is not applicable for Class E IP address";
	}
	else
	{
		cout << "Invalid IP address";
		return 0;
	}

	// // Finding the number of hosts
	// int hosts = pow(2, 8 - bits) - 2;
	// cout << "Bits = " << bits << endl;
	// cout << "Number of hosts: " << hosts << endl;

	return 0;
}