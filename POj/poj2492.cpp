#include <stdio.h>
#include <string.h>

const int N = 1e6+5;

int n, m, f[N], v[N];

int getfar(int x) {
	if (x != f[x]) {
		int t = f[x];
		f[x] = getfar(f[x]);
		v[x] = (v[x] + v[t])%2;
	}
	return f[x];
}

void init () {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) {
		f[i] = i;
		v[i] = 0;
	}
}

bool judge () {
	bool flag = false;
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		int p = getfar(a), q = getfar(b);
		if (p == q) {
			if (v[a] == v[b]) flag = true;
		} else {
			f[q] = p;
			v[q] = v[a] + 1 - v[b];
		}
	}
	return flag;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Scenario #%d:\n%s bugs found!\n", i, judge() ? "Suspicious" : "No suspicious");
		if (i != cas) printf("\n");
	}
	return 0;
}
