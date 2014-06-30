#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1005;
const int M = 15005;
typedef long long ll;

struct line {
	int u, v;
	ll l;
}way[M];

ll ans, costA, costB;
int n, m, k, t, cnt, f[N];

int get (int x) {
	return f[x] == x ? x : f[x] = get(f[x]);
}

bool cmp (const line& a, const line& b) {
	return a.l < b.l;
}

void init () {
	int a;
	ll b;

	cin >> costA >> costB;

	cnt = ans = 0;
	for (int i = 0; i <= n; i++)
		f[i] = i;

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &way[i].u, &way[i].v);
		cin >> b;
		way[i].l = b * costB;
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", &a);
		f[get(a)] = 0;
		ans += costA;
	}

	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d", &a);
		--a;

		int p = get(way[a].u);
		int q = get(way[a].v);
		ans += way[a].l;

		if (p != q)
			f[p] = q;
	}

	for (int i = 1; i <= n; i++) {
		way[m].u = i;
		way[m].v = 0;
		way[m].l = costA;
		m++;
	}

	sort (way, way + m, cmp);
}

ll solve () {
	for (int i = 0; i < m; i++) {
		int p = get(way[i].u);
		int q = get(way[i].v);

		if (p != q) {
			ans += way[i].l;
			f[p] = q;
			if (q == 0) cnt++;
		}
	}

	return ans - (cnt == 1  && k == 0 ? costA : 0);
}

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		init ();
		cout << solve () << endl;
	}
	return 0;
}
