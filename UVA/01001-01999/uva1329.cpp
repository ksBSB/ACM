#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
const int maxn = 20005;
const int MOD = 1000;

int N, f[maxn], d[maxn];

int getfar (int x) {
	if (x == f[x])
		return x;

	int root = getfar(f[x]);
	d[x] += d[f[x]];
	return f[x] = root;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i <= N; i++) {
			f[i] = i;
			d[i] = 0;
		}

		int u, v;
		char str[10];
		while (scanf("%s", str), str[0] != 'O') {
			if (str[0] == 'E') {
				scanf("%d", &u);
				getfar(u);
				printf("%d\n",  d[u]);
			} else if (str[0] == 'I') {
				scanf("%d%d", &u, &v);
				f[u] = v;
				d[u] = abs(u - v) % MOD;
			}
		}
	}
	return 0;
}
