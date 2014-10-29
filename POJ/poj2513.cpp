#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 5000005;
const int sigma_size = 26;
typedef pair<int,int> pii;

int N, E, far[maxn], cnt[maxn];
pii ed[maxn];

struct Tire {
	int sz, g[maxn][sigma_size];
	int val[maxn];

	void init();
	int idx(char ch);
	int insert(char* s);
}T;

inline int getfar(int x) {
	return x == far[x] ? x : far[x] = getfar(far[x]);
}

bool judge() {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		if (cnt[i]&1)
			ret++;
	}

	if (ret > 2)
		return false;

	for (int i = 0; i < E; i++) {
		int p = getfar(ed[i].first);
		int q = getfar(ed[i].second);
		if (p != q) {
			N--;
			far[p] = q;
		}
	}
	return N <= 1;
}

int main () {
	T.init();
	N = E = 0;
	char a[11], b[11];

	while (scanf("%s%s", a, b) == 2) {
		int p = T.insert(a);
		int q = T.insert(b);
		cnt[p]++, cnt[q]++;
		ed[E].first = p;
		ed[E].second = q;
		E++;
	}
	printf("%s\n", judge() ? "Possible" : "Impossible");
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx(char ch) {
	return ch - 'a';
}

int Tire::insert(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);
		if (g[u][v] == 0) {
			g[u][v] = sz;
			memset(g[sz], 0, sizeof(g[sz]));
			val[sz++] = 0;
		}

		u = g[u][v];
	}

	if (val[u] == 0) {
		val[u] = ++N;
		far[N] = N;
		cnt[N] = 0;
	}
	return val[u];
}
