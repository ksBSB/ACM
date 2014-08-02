#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;

void put (int i) {
	for (int j = 0; j < i; j++)
		printf("*");
	for (int j = 0; j < n - 2 * i; j++)
		printf("D");
	for (int j = 0; j < i; j++)
		printf("*");
	printf("\n");
}

int main () {
	scanf("%d", &n);

	for (int i = n/2; i >= 0; i--)
		put(i);

	for (int i = 1; i <= n/2; i++)
		put(i);
	return 0;
}
