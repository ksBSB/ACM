#include<iostream>
#include<string.h>
using namespace std;

int main()
{
	char str[100];

	while(1)
	{
		cin >> str;
		int n = strlen(str);

		if (n == 1 && str[0] == '0')
			break;
		
		int sum = 0;
		int t = 2;
		int a;

		do{
			a = str[n - 1] - '0';
			sum = sum + (t - 1) * a;
			t *= 2;
			n--;
		}while (n != 0);

		cout << sum << endl;
		memset(str, 0, sizeof(str));
	}
	return 0;
}
