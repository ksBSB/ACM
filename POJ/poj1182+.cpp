#include <stdio.h>
#include <string.h>

const int N = 1e5+5;

struct node {
	int u, v;
}f[N];
int n, k;

int getfar(int x, int& c) {
	if (x == f[x].u) {
		return x;
	} else {
		f[x].u = getfar(f[x].u, c);
		f[x].v = (c += f[x].v)%3;
		return f[x].u;
	}
}

void init () {
	for (int i = 0; i <= n; i++) {
		f[i].u = i; 
		f[i].v = 0;
	}
}

void solve () {
	int s, a, b, ans = 0;
	for (int i = 0; i < k; i++) {
		scanf("%d%d%d", &s, &a, &b);

		if (a > n || b > n) {
			ans++;
			continue;
		}

		int cp = 0, cq = 0;
		int p = getfar(a, cp), q = getfar(b, cq);
		cp %= 3; cq %= 3;

		if (s == 1) {

			if (p == q) {
				if (cp != cq)
					ans++;
				continue;
			} else {

				f[q].u = p;
				f[q].v = (cp + 3 - cq)%3;
			}

		} else {

			if (p == q) {
				if (cq != (cp + 1)%3)
					ans++;
				continue;
			} else {

				f[q].u = p;
				f[q].v = (cp + 4 - cq)%3;
			}
		}
	}
	printf("%d\n", ans);
}

int main () {
	scanf("%d%d", &n, &k);
	init ();
	solve ();
	return 0;
}
