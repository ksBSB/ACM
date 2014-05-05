#include<iostream>
#include<string.h>
using namespace std;

#define N 10

int num[N];
int n;
int cnt;
int ti;

int DFS(int deep)
{
	if(deep > ti)
		return 0;

	for (int i = 0; i < n - 1; i++)
	{
		if (num[i] > num[i + 1])
		{
			int t = num[i];
			num[i] = num[i + 1];
			num[i + 1] = t;

			DFS(deep + 1);

			t = num[i];
			num[i] = num[i + 1];
			num[i + 1] = t;
		}
	}

	for (int i = 0; i < n - 1; i++)
		if (num[i] > num[i + 1])
			return 0;

	if (deep == ti)	
		cnt++;
	else if (deep < ti)
	{
		ti = deep;
		cnt = 1;
	}
}

int main()
{
	int t = 1;
	int bo;
	while (cin >> n, n)
	{
		// Init.
		memset(num, 0, sizeof(num));
		bo = 0;
		ti = 100;

		// Read.
		for (int i = 0; i < n; i++)
			cin >> num[i];

		DFS(0);
		
		if (ti == 0)
			cnt = 0;

		cout << "There are " << cnt << " swap maps for input data set "<< t++ <<"." << endl;
	}
	return 0;
}
