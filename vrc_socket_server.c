// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define PORT 8080
int main()
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				   SO_REUSEADDR | SO_REUSEPORT, &opt,
				   sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t *)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("Connection established...\n");

	// Vertical reduncancy check
	printf("Enter the number of data bits: ");
	int n;
	scanf("%d", &n);
	int data[n];
	printf("Enter the data bits: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &data[i]);
	int pari = (int)ceil((float)n / 4.0);
	printf("Parity bits: %d\n", pari);
	int send_arr[n + pari];
	for (int i = 0; i < n; i++)
	{
		send_arr[i] = data[i];
	}
	int send_arr_index = n;
	for (int i = 0; i < n; i += 4)
	{
		int c = 0;
		for (int j = i; j < i + 4; j++)
		{
			if (data[j] == 1)
				c++;
		} 
		if (c % 2 == 0)
			send_arr[send_arr_index++] = 0;
		else
			send_arr[send_arr_index++] = 1;
	}
	printf("Data to be sent: ");
	for (int i = 0; i < n+pari; i++)
		printf("%d", send_arr[i]);
	printf("\n");
	send(new_socket, send_arr, sizeof(send_arr), 0);
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
