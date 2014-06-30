#include<iostream>
#include<string.h>
using namespace std;

#define N 10005

int main()
{
	int n, m;
	int num[N];
	int sum[N];
	int k, t = 1;

	while ( cin >> n >> m, n && m)
	{
		// Init.
		memset(num, 0, sizeof(num));

		// Read.
		for (int i = 0; i < n; i++)
		{
			cin >> k;
			num[k]++;
		}
		
		cout << "CASE# " << t++ << ":" << endl;
		// Count.
		for ( int i = 0; i < m; i++)
		{
			memset(sum, 0, sizeof(sum));
			cin >> k;
			if (num[k])
			{
				for (int j = 1; j < k; j++)
					sum[j] = sum[j - 1] + num[j];
				cout << k << " found at " << sum[k - 1] + 1 << endl;
			}
			else
				cout << k << " not found" << endl;
		}
	}
	return 0;
}
