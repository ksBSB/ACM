#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 1000005;

int N;
ll M;
int P, pri[maxn + 5], vis[maxn + 5];
int n, fac[maxn + 5], cnt[maxn + 5];

void init () {
	P = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= maxn; i++) {
		if (vis[i]) continue;
		pri[P++] = i;
		for (int j = i + i; j <= maxn; j += i)
			vis[j] = 1;
	}
}

void solve (int k) {
	n = 0;
	for (int i = 0; i < P; i++) {
		if (k % pri[i] == 0) {
			fac[n] = pri[i];
			cnt[n] = 0;
			while (k % pri[i] == 0) {
				cnt[n]++;
				k /= pri[i];
			}
			n++;
		}
	}
}

int get(int n, int x) {
	int ret = 0;
	while (x < n) {
		x = x + x;
		ret++;
	}
	return ret;
}

int main () {
	init();

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%llu", &N, &M);
		solve(N);

		int ans = 0;
		bool flag = true;
		for (int i = 0; i < n; i++) {
			int c = 0;
			while (M % fac[i] == 0) {
				c++;
				M /= fac[i];
			}
			if (c < cnt[i]) flag = false;
			ans = max(ans, get(c, cnt[i]));
		}
		printf("%d\n", M == 1 && flag ? ans : -1);
	}
	return 0;
}
