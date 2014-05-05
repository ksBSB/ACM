#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 60

int n;
char str[N];

int find(char tem[])
{
	int k = 0;
	for(int i = n - 1; i >= 0; i--)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			if(str[i] > str[j])
			{
				for(int f = i - 1; f >= j; f--)
					tem[k++] = str[f];
				return i;

			}
		}
		tem[k++] = str[i];
	}
	return -1;
}
int main()
{
	char tem[N];
	// Init.
	memset(str, 0, sizeof(str));

	while(cin >> str)
	{
		if(strcmp(str, "#") == 0)	
			break;

		n = strlen(str);
		memset(tem, 0, sizeof(tem));
		int m = find(tem);
		int k = strlen(tem);

		if(m == -1)
			cout << "No Successor" << endl;
		else
		{
			str[n - k -1] = str[m];
			sort(tem, tem + k);

			for(int i = 0; i < k; i++)
				str[n - k + i] = tem[i];

			cout << str << endl;
		}	
		memset(str, 0, sizeof(str));
	}
	return 0;}
