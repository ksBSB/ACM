#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e4 + 5;
const int maxm = 1e5 + 5;
const int mod = 1e9 + 7;

int N, v[maxm], a[maxm], l[maxm], r[maxm];
vector<int> G[maxn];

void init () {
	for (int i = 1; i < maxn; i++) {
		for (int j = i; j < maxn; j += i)
			G[j].push_back(i);
	}
}

int main () {
	init();
	while (scanf("%d", &N) == 1) {
		memset(v, 0, sizeof(v));
		memset(l, 0, sizeof(l));
		for (int i = 1; i <= N; i++) {
			scanf("%d", &a[i]);
			for (int j = 0; j < G[a[i]].size(); j++) {
				l[i] = max(l[i], v[G[a[i]][j]]);
			}
			v[a[i]] = i;
		}

		int ans = 0;
		for (int i = 0; i <= N; i++)
			r[i] = v[i] = N + 1;
		for (int i = N; i; i--) {
			for (int j = 0; j < G[a[i]].size(); j++) {
				r[i] = min(r[i], v[G[a[i]][j]]);
			}
			v[a[i]] = i;
			ans = (ans + (i - l[i]) * (r[i] - i) % mod ) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
