#include<iostream>
#include<math.h>
using namespace std;

int main()
{
	int n;

	while (cin >> n, n)
	{
		int a, b;
		// Find.
		for (int i = 0; ; i++)
			if (n <= pow(i + 1, 2))
			{	a = i;
				b = i + 1;
				break;
			}

		int t = pow(b, 2) - n;

		// Print.
		if (b % 2)
		{
			if (t < b)
				cout << t + 1 << " " << b << endl;
			else 
				cout << b << " " << n - pow(a, 2) << endl;
		}
		else 
		{
			if ( t < b)
				cout << b << " " << t + 1 << endl;
			else
				cout << n - pow(a, 2) << " " << b << endl;
		}
	}
	return 0;
}
