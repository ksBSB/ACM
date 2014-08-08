#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;

int n, g[maxn], s[maxn];

int SG (int l) {
	int vis[1000];
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++)
			vis[g[i]^g[j]] = 1;
	}

	int ret = -1;
	while (vis[++ret]);
	return ret;
}

void init () {
	g[0] = 0;
	for (int i = 1; i < maxn; i++)
		g[i] = SG(i);
}

int judge () {
	int ret = 0;
	for (int i = 0; i < n-1; i++) {
		if (s[i]&1)
			ret ^= g[n-1-i];
	}
	return ret;
}

void put_ans () {
	for (int i = 0; i < n-1; i++) {
		if (s[i] == 0)
			continue;

		s[i]--;
		for (int j = i+1; j < n; j++) {
			s[j]++;
			for (int k = j; k < n; k++) {
				s[k]++;
				if (judge() == 0) {
					printf(" %d %d %d\n", i, j, k);
					return;
				}
				s[k]--;
			}
			s[j]--;
		}
		s[i]++;
	}
}

int main () {
	init();
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &s[i]);

		printf("Game %d:", cas++);
		if (judge())
			put_ans();
		else
			printf(" -1 -1 -1\n");
	}
	return 0;
}
