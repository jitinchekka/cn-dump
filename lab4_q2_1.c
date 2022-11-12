// Bit stuffing
// Author: Jitin (CS20B1075)
#include <stdio.h>
int main()
{
	int n;
	printf("Enter the size of the message:");
	scanf("%d", &n);
	int a[100], count = 0;
	printf("Enter the bits of the message:");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	int flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 0)
		{
			flag = 1;
		}
		else if (a[i] == 1 && flag == 1)
		{
			flag = 2;
		}
		else if (a[i] == 1 && flag == 2)
		{
			flag = 3;
		}
		else if (a[i] == 1 && flag == 3)
		{
			flag = 4;
		}
		else if (a[i] == 1 && flag == 4)
		{
			flag = 5;
		}
		else if (a[i] == 1 && flag == 5)
		{
			n++;
			int pos = i + 2;
			for (i = n - 1; i >= pos; i--)
				a[i] = a[i - 1];

			// insert 0 at position pos
			a[pos - 1] = 0;
			flag = 0;
		}
		else
		{
			flag = 0;
		}
	}
	printf("The message after bitstuffing is:");
	for (int i = 0; i < n; i++)
	{
		printf("%d", a[i]);
	}
	return 0;
}