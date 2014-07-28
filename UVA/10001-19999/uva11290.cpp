#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 20;

int f[maxn], sf[maxn][maxn];

void init () {
	f[0] = 1;
	for (int i = 1; i < maxn; i++) {
		sf[i][0] = f[i-1] * f[0];
		for (int j = 1; j < i; j++)
			sf[i][j] = sf[i][j-1] + f[i-j-1] * f[j];
		f[i] = sf[i][i-1];
	}

	/*
	for (int i = 0; i < maxn; i++)
		printf("%d\n", f[i]);
		*/
}

char* solve (char* s, int n, int m) {
	if (n == 0)
		return s;

	if (n == 1) {
		*s++ = 'E';
		*s++ = 'S';
		return s;
	}

	int k = upper_bound(sf[n], sf[n]+n, m) - sf[n];

	if (k)
		m -= sf[n][k-1];

	int q = m / f[k], r = m % f[k];

	*s++ = 'E';
	s = solve(s, n - k - 1, q);
	*s++ = 'S';
	s = solve(s, k, r);
	return s;
}

int main () {
	init();
	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		n--;
		m--;
		if (m >=  f[n])
			printf("ERROR\n");
		else {
			char s[maxn*2];
			*solve(s, n, m) = '\0';
			printf("%s\n", s);
		}
	}
	return 0;
}
