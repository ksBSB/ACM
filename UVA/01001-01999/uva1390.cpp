#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;
const int mod = 1e5+7;

struct state {
	int c[maxn], flag;
	double val;

	void clear () { memset(c, 0, sizeof(c)); }
	int hash() {
		int x = 0;
		for (int i = 0; i < maxn; i++)
			x = (x * 30 + c[i]) % mod;
		return x;
	}
	bool operator == (const state& u) {
		for (int i = 0; i < maxn; i++)
			if (c[i] != u.c[i])
				return false;
		return true;
	}

	bool operator != (const state& u) {
		return !(*this == u);
	}

}start, ha[mod+7];

int n, m, f[maxn+5], s[maxn+5];
double dive;

int getfar (int x) {
	return f[x] == x ? x : f[x] = getfar(f[x]);
}

void link (int x, int y) {
	int p = getfar(x);
	int q = getfar(y);

	if (p == q)
		return;

	f[q] = p;
	s[p] += s[q];
}

void inserthash (state u) {
	int x = u.hash();
	while (ha[x].flag) {
		if (++x == mod)
			x = 0;
	}
	ha[x] = u;
	ha[x].flag = 1;
}

double gethash (state u) {
	int x = u.hash();
	while (ha[x].flag && ha[x] != u) {
		if (++x == mod)
			x = 0;
	}
	return ha[x] == u ? ha[x].val : -1;
}

void init () {
	dive = n * (n - 1) / 2.0;
	start.clear();
	for (int i = 0; i <= n; i++) {
		s[i] = 1;
		f[i] = i;
	}

	for (int i = 0; i < mod; i++)
		ha[i].flag = 0;

	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		link(a, b);
	}

	for (int i = 1; i <= n; i++) {
		if (f[i] == i)
			start.c[i-1] = s[i];
	}
}

double solve (state u) {
	sort(u.c, u.c+maxn);
	if (u.hash() == n)
		return 0;

	double x = gethash(u);
	
	if (x != -1.0)
		return x;

	double ans = 0, tmp = 0;

	for (int i = 0; i < maxn; i++)
		tmp += u.c[i] * (u.c[i] - 1) / 2.0;

	for (int i = 0; i < maxn; i++) {

		if (u.c[i] == 0)
			continue;

		for (int j = i+1; j < maxn; j++) {

			if (u.c[j] == 0)
				continue;

			state v = u;
			v.c[i] += v.c[j];
			v.c[j] = 0;
			ans += u.c[i] * u.c[j] * solve(v);
		}
	}

	ans /= dive;
	ans++;
	ans /= (1 - tmp / dive);
	u.val = ans;
	inserthash(u);
	return ans;
}

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		printf("%.10lf\n", solve(start));
	}
	return 0;
}
