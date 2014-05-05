#include<iostream>
#include<string.h>
using namespace std;

#define N 100

int judge_pa(char str[])
{
	int n = strlen(str);

	for (int i = 0; i < n / 2; i++)
		if (str[i] != str[n - i - 1])
			return 0;
	return 1;
}

int judge_mi(char str[])
{
	int n = strlen(str);
	for (int i = 0; i <= n / 2; i++)
	{
		switch(str[i])
		{
			case 'E':
				if (str[n - i -1] != '3')
					return 0;
				break;
			case 'J':
				if (str[n - i - 1] != 'L')
					return 0;
				break;
			case 'L':
				if (str[n - i - 1] != 'J')
					return 0;
				break;
			case 'S':
				if (str[n - i - 1] != '2')
					return 0;
				break;
			case '2':
				if (str[n - i - 1] != 'S')
					return 0;
				break;
			case '3':
				if (str[n - i - 1] != 'E')
					return 0;
				break;
			case 'Z':
				if (str[n - i - 1] != '5')
					return 0;
				break;
			case '5':
				if (str[n - i - 1] != 'Z')
					return 0;
				break;
			case 'A':
			case 'H':
			case 'I':
			case 'M':
			case 'O':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case '1':
			case '8':
				if (str[i] != str[n - i - 1])
					return 0;
				break;
			default:
				return 0;
		}
	}
	return 1;
}

int main ()
{
	char str[N];
	int bool_pa;
	int bool_mi;

	while (cin >> str)
	{
		// Judge.
		bool_pa = judge_pa(str);
		bool_mi = judge_mi(str);

		// Print.
		if (bool_pa && bool_mi)
			cout << str << " -- is a mirrored palindrome." << endl;
		else if (bool_pa)
			cout << str << " -- is a regular palindrome." << endl;
		else if (bool_mi)
			cout << str << " -- is a mirrored string." << endl;
		else 
			cout << str << " -- is not a palindrome." << endl;
		cout << endl;

		// Init.
		memset(str, 0, sizeof(str));
	}
	return 0;
}
		
