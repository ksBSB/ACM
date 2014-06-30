#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 17;
const int M = 105;

int n, r, c, v[1<<N][M], area[M], sum[1<<N];
bool d[1<<N][M];

void init () {
	memset(d, 0, sizeof(d));
	memset(v, 0, sizeof(v));
	memset(sum, 0, sizeof(sum));

	scanf("%d%d", &r, &c);
	for (int i = 0; i < n; i++) scanf("%d", &area[i]);

	for (int i = 0; i < (1<<n); i++) {
		for (int j = 0; j < n; j++) if ((1<<j) & i) {
			sum[i] += area[j];
		}
	}
}

int bitcount(int x) {
	return x == 0 ? 0 : bitcount(x/2) + (x&1);
}

bool dp(int S, int x) {
	if (v[S][x]) return d[S][x];
	bool& ans = d[S][x];
	v[S][x] = 1;

	if (bitcount(S) == 1) return ans = true;
	int y = sum[S] / x;
	for (int S0 = (S-1)&S; S0; S0 = (S0-1)&S) {
		int S1 = S - S0;
		if (sum[S0] % x == 0 && dp(S0, min(sum[S0]/x, x)) && dp(S1, min(sum[S1]/x, x))) return ans = true;
		if (sum[S0] % y == 0 && dp(S0, min(sum[S0]/y, y)) && dp(S1, min(sum[S1]/y, y))) return ans = true;
	}
	return ans = false;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init ();
		bool flag = false;
		if (sum[(1<<n)-1] != r*c || sum[(1<<n)-1] % r != 0) flag = false;
		else flag = dp((1<<n)-1, min(r, c));
		printf("Case %d: %s\n", cas++, flag ? "Yes" : "No");
	}
	return 0;
}
