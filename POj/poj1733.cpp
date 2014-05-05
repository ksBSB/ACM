#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;
map<int, int> f;
map<int, int> v;
int n, m;

void judge (int x) {
	if (f.count(x)) return ;
	f[x] = x;
	v[x] = 0;
}

int getfar (int x) {
	if (x != f[x]) {
		int t = f[x];
		f[x] = getfar(f[x]);
		v[x] = (v[x] + v[t]) % 2;
	}
	return f[x];
}

int solve () {
	int a, b, ans = n;
	char str[10];
	for (int i = 0; i < n; i++) {
		scanf("%d%d%s", &a, &b, str);
		if (ans != n) continue;
		a--;
		judge(a);
		judge(b);

		int s = (strcmp(str, "odd") == 0) ? 1 : 0;
		int p = getfar(a), q = getfar(b);

		if (p == q) {
			if (s == 1 && v[a] == v[b]) ans = i;
			if (s == 0 && v[a] != v[b]) ans = i;
		} else {
			f[q] = p;
			v[q] = (v[b] + 2 + s + v[a])%2;
		}
	}
	return ans;
}

int main () {
	while (scanf("%d%d", &m, &n) == 2) {
		f.clear();
		v.clear();
		printf("%d\n", solve ());
	}
	return 0;
}
