#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 3 * 1e5+5;

struct edge {
	int u, v, w;
}s[maxn];

bool cmp (const edge& a, const edge& b) {
	return a.w < b.w;
}

int n, m, d[maxn], f[maxn], val[maxn];

int main () {
	scanf("%d%d", &n, &m);
	memset(d, 0, sizeof(d));
	memset(f, 0, sizeof(f));
	memset(val, 0, sizeof(val));

	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &s[i].u, &s[i].v, &s[i].w);
	sort(s, s + m, cmp);

	for (int i = 0; i < m; i++) {

		int j;
		for (j = i; s[j].w == s[i].w && j < m; j++);

		for (int k = i; k < j; k++)
			d[s[k].v] = max(d[s[k].v], f[s[k].u] + 1);
		for (int k = i; k < j; k++)
			f[s[k].v] = d[s[k].v];
		i = j - 1;
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
