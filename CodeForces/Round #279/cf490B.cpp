#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;
const int maxm = 1e5 * 2 + 5;

int N, ans[maxm];
int v[maxn], f[maxn];

void init () {
	scanf("%d", &N);
	memset(v, 0, sizeof(v));
	memset(f, -1, sizeof(f));

	int a, b;
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &a, &b);
		f[a] = b;
		v[a]++, v[b]++;
	}
}

void solve(int b, int x) {
	while (b > 0) {
		ans[x] = b;
		x += 2;
		b = f[b];
	}
}

int main () {
	init();

	solve(f[0], 2);
	for (int i = 1; i <= 1e6; i++)
		if (v[i] == 1 && f[i] >= 0) {
			solve(i, 1);
			break;
		}

	for (int i = 1; i <= N; i++)
		printf("%d%c", ans[i], i == N ? '\n' : ' ');
	return 0;
}
