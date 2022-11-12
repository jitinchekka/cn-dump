// Byte stuffing
// Author : Jitin (CS20B1075)
#include <stdio.h>
#include <string.h>

int main()
{
	char a[100];
	int i;
	printf("Enter the message:");
	scanf("%s", a);
	int n = strlen(a);
	for (i = 0; i < n; i++)
	{
		if (a[i] == 'F' || a[i] == 'E')
		{
			int pos = i + 1;
			n++;
			for (int j = n - 1; j >= pos; j--)
			{
				a[j] = a[j - 1];
			}

			a[pos - 1] = 'E';
			i++;
		}
	}
	a[n] = '\0';
	printf("The byte stuffed message is:%s", a);
	return 0;
}