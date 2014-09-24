#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 5000;

int c[maxn+5];

void anti_prime (int n) {
	memset(c, 0, sizeof(c));
	for (int i = 2; i <= n; i++) {

		for (int j = i; j <= n; j += i)
			c[j]++;
	}
}

int main () {
	anti_prime(maxn);
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int l, r, x, s;
		scanf("%d%d", &l, &r);
		x = l, s = c[l];
		for (int i = l + 1; i <= r; i++)
			if (c[i] > s) {
				s = c[i];
				x = i;
			}
		printf("%d\n", x);
	}
	return 0;
}
