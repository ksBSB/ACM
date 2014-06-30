#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1000005;

int n, m, k, v[N], g[N];

void init() {
	memset(g, 0, sizeof(g));
	memset(v, 0, sizeof(v));

	scanf("%d%d%d", &n, &m, &k);
	g[1] = 1; g[2] = 2; g[3] = 3;
	for (int i = 4; i <= n; i++)
		g[i] = (g[i-1] + g[i-2] + g[i-3]) % m + 1;
}

bool solve() {
	int l = 1, r = 1, c = 0;
	int ans = n + 1;
	while (r <= n) {
		int t = g[r++];
		v[t]++;
		if (t <= k && v[t] == 1) c++;

		while (l < r && c == k) {
			ans = min(ans, r - l);
			t = g[l++];
			v[t]--;
			if (t <= k && v[t] == 0) c--;
		}
	}
	if (ans <= n) {
		printf("%d\n", ans);
		return false;
	}
	return true;
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: ", i);
		if (solve()) printf("sequence nai\n");
	}
	return 0;
}
