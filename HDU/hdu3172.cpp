#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int N, M, far[maxn], cnt[maxn];
map<string, int> G;

inline void check(string s) {
	if (G.count(s))
		return;
	cnt[M] = 1;
	far[M] = M;
	G[s] = M++;
}

int getfar(int x) {
	return x == far[x] ? x : far[x] = getfar(far[x]);
}

void merge (int u, int v) {
	int fu = getfar(u);
	int fv = getfar(v);

	if (fu != fv) {
		far[fv] = fu;
		cnt[fu] += cnt[fv];
	}
	cout << cnt[fu] << endl;
}

int main () {
	int cas;
	while (scanf("%d", &cas) == 1) {
		while (cas--) {
			M = 0;
			G.clear();
			char a[20], b[20];
			scanf("%d", &N);

			for (int i = 0; i < N; i++) {
				scanf("%s%s", a, b);
				check(a); check(b);
				merge(G[a], G[b]);
			}
		}
	}
	return 0;
}
