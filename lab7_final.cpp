#include <bits/stdc++.h>
using namespace std;

#define DELIM "."

int arr1[4];
int COUNT = 0;
int sm[32];

int Validity(char *IP_address)
{
	while (*IP_address)
	{
		if (*IP_address >= '0' && *IP_address <= '9')
		{
			++IP_address;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

// To check validity of the ip address
int valid_IP(char *IP_address)
{
	int i, num, dots = 0;
	char *ptr;

	if (IP_address == NULL)
	{
		return 0;
	}
	ptr = strtok(IP_address, DELIM);
	if (ptr == NULL)
	{
		return 0;
	}
	while (ptr)
	{
		if (!Validity(ptr))
		{
			return 0;
		}
		num = atoi(ptr);
		if (num >= 0 && num <= 255)
		{
			ptr = strtok(NULL, DELIM);
			if (ptr != NULL)
			{
				++dots;
			}
		}
		else
		{
			return 0;
		}
	}
	if (dots != 3)
	{
		return 0;
	}
	return 1;
}

// To find the class of given ip address
int Class(int n)
{
	int b1[8];
	int i = 7;
	for (int i = 0; i < 8; i++)
	{
		b1[i] = 0;
	}

	while (n > 0)
	{
		b1[i] = n % 2;
		n = n / 2;
		i--;
	}
	// The first bit is 0 for class A
	if (b1[0] == 0)
	{
		return 1;
	}
	// The first bits for class B is 10
	else if (b1[0] == 1 & b1[1] == 0)
	{
		return 2;
	}
	// The first bits for class C is 110
	else if (b1[0] == 1 & b1[1] == 1 & b1[2] == 0)
	{
		return 3;
	}
	// The first bits for class D is 1110
	else if (b1[0] == 1 & b1[1] == 1 & b1[2] == 1 & b1[3] == 0)
	{
		return 4;
	}
	// The first bits for class E is 1111
	else if (b1[0] == 1 & b1[1] == 1 & b1[2] == 1 & b1[3] == 1 & b1[4] == 1)
	{
		return 5;
	}
	return 0;
}

int FindPower(int n)
{
	if (n == 0)
	{
		return 0;
	}
	else if (ceil(log2(n)) == floor(log2(n)))
	{
		return (int)log2(n);
	}
	return 0;
}

void binary_conversion(int n, int arr[], int k)
{
	int bin[8];
	int i = 7;
	for (int i = 0; i < 8; i++)
	{
		bin[i] = 0;
	}
	while (n > 0)
	{
		bin[i] = n % 2;
		n = n / 2;
		i--;
	}
	int count = 0;
	for (int j = k * 8; j < (k * 8) + 8; j++)
	{
		arr[j] = bin[count];
		count++;
	}
}

void decimal_conversion(int arr[])
{
	int count = 0;
	while (count < 4)
	{
		int i = 7;
		int sum = 0;
		for (int j = count * 8; j < (count * 8) + 8; j++)
		{
			sum += arr[j] * pow(2, i);
			i--;
		}
		arr1[count] = sum;
		count++;
	}
	cout << arr1[0] << "." << arr1[1] << "." << arr1[2] << "." << arr1[3];
}

void convert_decimal1(int arr[])
{
	int count = 0;
	while (count < 4)
	{
		int i = 7;
		int sum = 0;
		for (int j = count * 8; j < (count * 8) + 8; j++)
		{
			sum += arr[j] * pow(2, i);
			i--;
		}
		arr1[count] = sum;
		count++;
	}
	cout << arr1[0] << "." << arr1[1] << "." << arr1[2] << "." << arr1[3];

	decimal_conversion(sm);
	cout << "\t\tI" << COUNT << "\n";
	COUNT++;
}

void print(int arr[], int n, int k)
{
	for (int i = k + n; i < 32; i++)
	{
		arr[i] = 0;
	}
	cout << "The subnet ID is : ";
	decimal_conversion(arr);
	for (int i = k + n; i < 32; i++)
	{
		arr[i] = 1;
	}
	cout << endl;

	cout << "The Direct Broadcast Address : ";
	decimal_conversion(arr);
	cout << endl;
	cout << endl;
}

void fn(int n, int arr[], int i, int k)
{
	if (i == n)
	{
		print(arr, n, k);
		return;
	}

	arr[i + k] = 0;
	fn(n, arr, i + 1, k);
	arr[i + k] = 1;
	fn(n, arr, i + 1, k);
}

void print1(int arr[], int n, int k)
{

	for (int i = k + n; i < 32; i++)
	{
		arr[i] = 0;
	}
	convert_decimal1(arr);
}

void generate1(int n, int arr[], int i, int k)
{
	if (i == n)
	{
		print1(arr, n, k);
		return;
	}
	arr[i + k] = 0;
	generate1(n, arr, i + 1, k);
	arr[i + k] = 1;
	generate1(n, arr, i + 1, k);
}

void print2(int arr[], int n, int k)
{

	for (int i = k + n; i < 32; i++)
	{
		arr[i] = 0;
	}
	decimal_conversion(arr);
	cout << " To ";
	for (int i = k + n; i < 32; i++)
	{
		arr[i] = 1;
	}
	decimal_conversion(arr);
	cout << endl;
}

void generate2(int n, int arr[], int i, int k)
{
	if (i == n)
	{
		print2(arr, n, k);
		return;
	}
	arr[i + k] = 0;
	generate2(n, arr, i + 1, k);
	arr[i + k] = 1;
	generate2(n, arr, i + 1, k);
}

int main()
{
	char ip[20];
	char ip1[20];
	int tot_bin[32];
	int tot_bin1[32];
	char *ch;
	int i = 0;
	char *ch1;
	char ch3[100];
	int num1[100];
	int res;
	int subnet;
	int j;

	cout << "Enter the IP Address as : ";
	cin >> ip;
	// cpy the ip into ip1
	strcpy(ip1, ip);

	// validiting the ip address
	res = valid_IP(ip);

	ch = strtok(ip1, ".");
	while (ch != NULL)
	{
		int n = atoi(ch);
		num1[i] = n;
		i++;
		ch = strtok(NULL, ".");
	}

	if (res != 0)
	{
		for (j = 0; j < i; j++)
		{
			binary_conversion(num1[j], tot_bin, j);
		}
		for (int i = 0; i < 32; i++)
		{
			tot_bin1[i] = tot_bin[i];
		}
		int k = Class(num1[0]);
		cout << "Enter no of subnets: ";
		cin >> subnet;

		if (FindPower(subnet) != 0)
		{
			if (k == 1)
			{
				int n1 = FindPower(subnet);
				if (n1 <= 22 && n1 >= 1)
				{
					int a = 8 + n1;
					int b = 32 - a;
					int ip = pow(2, b);
					int host = ip - 2;

					cout << "\n\nThe Number of IP Addresses is : " << ip << endl;
					cout << "The Number of hosts per subnet : " << host << "\n\n";
					fn(n1, tot_bin, 0, 8);
					for (int q = 0; q < 32; q++)
					{
						if (q < a)
						{
							sm[q] = 1;
						}
						else
						{
							sm[q] = 0;
						}
					}
					cout << "The range of the IP Address is : " << endl;
					generate2(n1, tot_bin1, 0, 8);

					cout << "\n\nSubnetID\t\tsubnet Mask\t\tInterface\n";
					for (int i = 8 + n1; i < 32; i++)
					{
						tot_bin1[i] = 0;
					}
					generate1(n1, tot_bin1, 0, 8);
				}
				else
				{
					cout << "Maximum number subnets possible is 2 power 22";
				}
			}
			else if (k == 2)
			{
				int n1 = FindPower(subnet);
				if (n1 <= 14 && n1 >= 1)
				{
					int a = 16 + n1;
					int b = 32 - a;
					int ip = pow(2, b);
					int host = ip - 2;

					cout << "\n\nThe Number of IP Addresses is : " << ip << "\n";
					cout << "The Number of hosts per subnet : " << host << "\n\n";
					fn(n1, tot_bin, 0, 16);
					for (int q = 0; q < 32; q++)
					{
						if (q < a)
						{
							sm[q] = 1;
						}
						else
						{
							sm[q] = 0;
						}
					}
					cout << "The range of the IP Address is : " << endl;
					generate2(n1, tot_bin1, 0, 16);
					cout << "\n\nSubnetID\t\tsubnet Mask\t\tInterface\n";
					for (int i = 16 + n1; i < 32; i++)
					{
						tot_bin1[i] = 0;
					}
					generate1(n1, tot_bin1, 0, 16);
				}
				else
				{
					cout << "Maximum number subnets possible is 2 power 22";
				}
			}
			else if (k == 3)
			{
				int n1 = FindPower(subnet);
				if (n1 <= 6 && n1 >= 1)
				{
					int a = 24 + n1;
					int b = 32 - a;
					int ip = pow(2, b);
					int host = ip - 2;
					cout << "\n\nThe Number of IP Addresses is : " << ip << "\n";
					cout << "The Number of hosts per subnet is : " << host << "\n\n";
					fn(n1, tot_bin, 0, 24);
					for (int q = 0; q < 32; q++)
					{
						if (q < a)
						{
							sm[q] = 1;
						}
						else
						{
							sm[q] = 0;
						}
					}
					cout << "The range of the IP Address is : " << endl;
					generate2(n1, tot_bin1, 0, 24);
					cout << "\n\nSubnetID\t\tsubnet Mask\t\tInterface\n";
					for (int i = 24 + n1; i < 32; i++)
					{
						tot_bin1[i] = 0;
					}
					generate1(n1, tot_bin1, 0, 24);
				}
				else
				{
					cout << "Maximum number subnets possible is 2 power 22";
				}
			}
			else
			{
				cout << "Subnetting is not possible" << endl;
			}
		}
		else
		{
			cout << "\n Number of subnets in not in the power of two!\n";
		}
	}
	else
	{
		cout << "\n Ip address is inavlid!!! ";
		cout << "\n";
	}
	return 0;
}