#include <cstdio>
#include <cstring>

const int N = 10;

int main () {
	int n, k, a, c = 0;

	scanf("%d%d", &n, &k);
	k = 5 - k;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		if (a <= k)
			c++;
	}
	printf("%d\n", c/3);
	return 0;
}
