#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

#define N 100

int main()
{
	int n;
	char str[N];

	cin >> n;

	while(n--)
	{
		// Init.
		memset(str, 0, sizeof(str));

		// Read.
		int m, b;
		cin >> m >> b;
		for(int i = 0; i < m; i++)
		{
			if(i < b)
				str[i] = '1';
			else
				str[i] = '0';
		}
		sort(str, str + m);
		do{
			cout << str << endl;
		}while(next_permutation(str, str + m));
		if(n)
			cout << endl;
	}
	return 0;}
