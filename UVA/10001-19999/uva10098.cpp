#include<iostream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;

#define N 20

int main()
{
	int n;
	char str[N];

	scanf("%d", &n);

	while(n--)
	{
		// Init.
		memset(str, 0, sizeof(str));

		// Read.
		scanf("%s", str);
		int m = strlen(str);
		sort(str, str + m);
		do{
			printf("%s\n", str);
		}while(next_permutation(str, str + m));
		cout << endl;
	}
	return 0;}
