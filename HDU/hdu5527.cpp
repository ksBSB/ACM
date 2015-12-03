#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int V[] = {0, 1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
const int maxn = 15;
typedef long long ll;

int N, S[maxn], ans;
ll T[maxn];

void dfs (int p, int n, int d) {
	if (p < 0) return;

	if (d == 0) {
		if (p == 0) ans = max(n, ans);
		return;
	}

	ll tmp = max(p - T[d-1], 0LL);
	int k = tmp / V[d] + (tmp % V[d] ? 1 : 0);
	if (k > S[d]) return;
	dfs(p - k * V[d], n + k, d - 1);

	k++;
	if (k <= S[d])
		dfs(p - k * V[d], n + k, d - 1);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= 10; i++) scanf("%d", &S[i]);

		T[0] = 0;
		for (int i = 1; i <= 10; i++) T[i] = T[i-1] + 1LL * S[i] * V[i];

		ans = 0;
		dfs(N, 0, 10);

		if (ans) printf("%d\n", ans);
		else printf("-1\n");
	}
	return 0;
}
