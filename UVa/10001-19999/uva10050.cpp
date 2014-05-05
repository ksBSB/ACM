#include<iostream>
#include<string.h>
using namespace std;

#define N 110

int num[N];

int main()
{
	int n;
	cin >> n;

	while (n--)
	{
		// Init.
		memset(num, 0,sizeof(num));

		int t, p, cnt = 0;
		cin >> t >> p;

		for (int i = 0; i < p; i++)
			cin >> num[i];

		for (int j = 1; j <= t; j++)
			for (int i = 0; i < p; i++)
				if (j % num[i] == 0 && j % 7 != 0 && j % 7 != 6)
					{
						cnt++;
						break;
					}

		cout << cnt << endl;
	}
	return 0;
}
