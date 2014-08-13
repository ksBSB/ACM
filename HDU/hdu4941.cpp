#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
map<pii, int> g;
map<int , int> X;
map<int, int> Y;

int N, M, K;

void init () {
	g.clear();
	X.clear();
	Y.clear();

	int a, b, w;
	scanf("%d%d%d", &N, &M, &K);

	for (int i = 0; i < K; i++) {
		scanf("%d%d%d", &a, &b, &w);
		g[make_pair(a,b)] = w;
	}
}

int get (map<int, int>& u, int x) {
	if (u.count(x))
		return u[x];
	return u[x] = x;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		scanf("%d", &n);

		printf("Case #%d:\n", kcas);

		int s, a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &s, &a, &b);
			if (s == 1) {
				int p = get(X, a);
				int q = get(X, b);
				swap(X[a], X[b]);
			} else if (s == 2) {
				int p = get(Y, a);
				int q = get(Y, b);
				swap(Y[a], Y[b]);
			} else {
				int p = get(X, a);
				int q = get(Y, b);
				printf("%d\n", g.count(make_pair(p, q)) ? g[make_pair(p, q)] : 0);
			}
		}
	}
	return 0;
}
