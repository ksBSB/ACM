#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const ll x = 123;
const int maxr = 10005;
const int maxc = 80;

int N, M, jump[maxr];
ll r[maxr], c[maxc];
char s[maxr][maxc];

void init () {
	for (int i = 1; i <= N; i++)
		scanf("%s", s[i] + 1);
	memset(r, 0, sizeof(r));
	memset(c, 0, sizeof(c));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			r[i] = r[i] * x + s[i][j];
	}

	for (int j = 1; j <= M; j++) {
		for (int i = 1; i <= N; i++)
			c[j] = c[j] * x + s[i][j];
	}
}

int kmp (int n, ll* a) {
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while(p && a[p+1] != a[i])
			p = jump[p];

		if (a[p+1] == a[i])
			p++;
		jump[i] = p;
	}
	return n - jump[n];
}

int solve () {
	return kmp(N, r) * kmp(M, c);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
