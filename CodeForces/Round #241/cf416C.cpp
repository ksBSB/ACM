#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
struct state {
	int id, val, sum;
	state () {
	}
}g[N], t[N];
int n, m, v[N];

bool cmpS (const state& a, const state& b) {
	if (a.val != b.val) return a.val > b.val;
	return a.sum > b.sum;
}

bool cmpT (const state& a, const state& b) {
	return a.sum < b.sum;
}

void init () {
	memset(v, 0, sizeof(v));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &g[i].sum, &g[i].val);
		g[i].id = i;
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &t[i].sum);
		t[i].id = i;
	}

	sort(g, g + n, cmpS);
	sort(t, t + m, cmpT);
}

void solve () {
	int ans = 0, cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (g[i].sum <= t[j].sum) {
				cnt++;
				ans += g[i].val;
				v[g[i].id] = t[j].id + 1;
				t[j].sum = 0;;
				break;
			}
		}
	}
	printf("%d %d\n", cnt, ans);
	for (int i = 0; i < n; i++) {
		if (v[i]) printf("%d %d\n",	i + 1, v[i]);
	}
}

int main () {
	init ();
	solve ();
	return 0;
}
