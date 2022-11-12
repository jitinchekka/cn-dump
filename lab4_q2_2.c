// Character Count
// Author: Jitin (CS20B1075)
#include <stdio.h>
int main()
{
	int n;
	printf("Enter the size of the message:");
	scanf("%d", &n);

	int len_bits = n / 4, count = 0;
	if (n < 4)
	{
		len_bits = 1;
	}
	int size = n + len_bits;
	int a[size];

	// taking input message
	printf("Enter the message:");
	for (int i = 0; i < size; i++)
	{
		if (i % 5 != 0)
		{
			scanf("%d", &a[i]);
		}
		else if (count < len_bits)
		{
			count++;
			a[i] = 0;
		}
		else
		{
			scanf("%d", &a[i]);
		}
	}
	// breaking the message into 4 bits each
	for (int i = 0; i < size; i += 5)
	{
		if ((size - i) <= 8)
		{
			a[i] = size - i - 1;
			break;
		}
		else
		{
			a[i] = 4;
		}
	}

	// printing the details
	printf("The output message is:");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}