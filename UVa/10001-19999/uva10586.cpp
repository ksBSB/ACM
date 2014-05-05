#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 10005;

int n, k, a[N];

int main () {
	while (scanf("%d%d", &n, &k) == 2 && n != -1 && k != -1) {
		for (int i = n; i >= 0; i--)
			scanf("%d", &a[i]);

		int t = max(n - k, -1);
		for (int i = 0; i <= t; i++)
			a[i+k] -= a[i];

		printf("%d", a[n]);
		for (int i = n - 1; i > t; i--)
			printf(" %d", a[i]);
		printf("\n");
	}
	return 0;
}
