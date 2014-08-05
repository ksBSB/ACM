#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 40000;
int N, M, pos, v[maxn+5], c[2][maxn*2+5];

void init () {
	int a;
	v[0] = 0;

	for (int i = 1; i <= N; i++) {
		v[i] = v[i-1];
		scanf("%d", &a);
		if (a > M)
			v[i]++;
		if (a == M)
			pos = i;
	}
}

int solve () {
	memset(c, 0, sizeof(c));

	for (int i = 1; i <= pos; i++) {
		int tmp = i - 2 * v[i-1];
		c[0][tmp + maxn]++;
	}

	for (int i = pos; i <= N; i++) {
		int tmp = i - 2 * v[i];
		c[1][tmp + maxn]++;
	}

	int ans = 0;
	for (int i = 0; i <= maxn*2; i++)
		ans += c[0][i] * c[1][i];
	return ans;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
