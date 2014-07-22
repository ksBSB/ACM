#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

bool flag;
int n, l[maxn], r[maxn];
int cnt, ans[maxn], v[maxn];

inline void cat (char* str, int x) {
	bool sign = false;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			if (sign)
				r[x] |= (1<<(str[i] - 'A'));
			else
				l[x] |= (1<<(str[i] - 'A'));
		} else
			sign = true;
	}
}

inline void init () {
	char str[maxn];
	flag = true;
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		cat(str, i);
	}
}

inline void put (int k) {
	printf("     FD %d is redundant using FDs:", k + 1);
	for (int i = 0; ans[i] != -1; i++)
		printf(" %d", ans[i]);
	printf("\n");
}

bool check (int s, int k) {
	int vis[maxn];
	memset(vis, 0, sizeof(vis));

	while (true) {
		bool stop = true;
		for (int i = 0; i < n; i++) {
			if (vis[i] || v[i])
				continue;

			if ((s & l[i]) != l[i])
				continue;

			vis[i] = 1;
			s |= r[i];
			stop = false;
		}

		if (stop)
			break;
	}

	return (s | r[k]) != s;
}

bool dfs (int d, int s, int k) {
	ans[d] = -1;

	if ((s & r[k]) == r[k])
		return true;

	if (check(s, k))
		return false;

	for (int i = 0; i < n; i++) {
		if (v[i])
			continue;

		if ((s & l[i]) != l[i])
			continue;

		if ((s | r[i]) == s)
			continue;

		v[i] = 1;
		if (dfs(d, s, k))
			return true;

		ans[d] = i + 1;
		if (dfs(d+1, s | r[i], k))
			return true;
		v[i] = 0;
	}
	return false;
}

void solve () {
	for (int i = 0; i < n; i++) {
		memset(v, 0, sizeof(v));
		v[i] = 1;
		if (dfs(0, l[i], i)) {
			put(i);
			flag = false;
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();

		printf("Set number %d\n", cas++);
		solve();
		if (flag)
			printf("     No redundant FDs.\n");
		printf("\n");
	}
	return 0;
}
