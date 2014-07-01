#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2005;
const int M = 505;

int n, m, f[M], r[N];
int u[N], v[N], s[N], vis[N];

int getfar(int x) {
	if (x != f[x]) {
		int t = f[x];
		f[x] = getfar(f[x]);
		r[x] = (r[x] + r[t])%3;
	}
	return f[x];
}

void read () {
	char ch;
	for (int i = 0; i < m; i++) {
		scanf("%d", &u[i]);
		while ((ch = getchar()) == ' ') ;
		scanf("%d", &v[i]);

		if (ch == '=') 
			s[i] = 0;
		else if (ch == '<')
			s[i] = 1;
		else
			s[i] = 2;
	}
}

void init () {
	for (int i = 0; i <= n; i++)
		f[i] = i;
	memset(r, 0, sizeof(r));
}

void solve () {
	int ans = -1, rec = 0;

	for (int i = 0; i < n; i++) {
		init ();

		int j, tmp = 0;
		for (j = 0; j < m; j++) {
			int a = u[j];
			int b = v[j];

			if (a == i || b == i) continue;

			int p = getfar(a);
			int q = getfar(b);

			if (p == q) {
				if (r[a] != (r[b] + s[j])%3) {
					tmp = j + 1;
					break;
				}
			} else {
				f[p] = q;
				r[p] = (r[b] + s[j] - r[a] + 3) % 3;
			}
		}

		if (j == m) {
			if (ans == -1) {
				ans = i;
			} else {
				printf("Can not determine\n");
				return;
			}
		} else 
			rec = max(rec, tmp);
	}

	if (ans == -1)
		printf("Impossible\n");
	else
		printf("Player %d can be determined to be the judge after %d lines\n" , ans , rec);
}

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		read ();
		solve ();
	}
	return 0;
}
