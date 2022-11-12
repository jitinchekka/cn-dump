// Client side C/C++ program to demonstrate Socket
// programming
#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
using namespace std;

int main(int argc, char const *argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
							 sizeof(serv_addr))) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	cout << "Testing connection...\n";
	printf("Connection Established\n");
	int n;
	cout << "Enter n\n";
	cin >> n;
	int data[n] = {0};
	for (int i = 0; i < n; i++)
	{
		recv(sock, data + i, sizeof(int), 0);
	}

	// Selective repeat
	cout << "Enter the window size N:\n";
	int N;
	cin >> N;
	cout << "Enter i such that every ith bit is missed\n";
	int fail;
	cin >> fail;
	// cout << "N = " << N << " fail = " << fail << endl;
	vector<int> ans;
	cout << "Sent data is:\n";
	int sent = 0;
	for (int i = 1; i <= n; i++)
	{
		ans.push_back(i);
		sent++;
		if (sent % fail == 0)
		{
			int j = 0;
			for (j = 1; j < N; j++)
			{
				if (i + j <= n)
				{
					ans.push_back(i + j);
					sent++;
				}
			}
			ans.push_back(i);
			i = i + j - 1;
		}
	}
	for (auto x : ans)
		cout << x << " ";
	// closing the connected socket
	close(client_fd);
	return 0;
}