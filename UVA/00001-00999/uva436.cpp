#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M, L[maxn], R[maxn];
double D[maxn], K[maxn];
char s[maxn], t[maxn];
map<string, int> G;

void init () {
	G.clear();
	for (int i = 1; i <= N; i++) {
		scanf("%s", s);
		G[s] = i;
	}
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%s%lf%s", s, &K[i], t);
		L[i] = G[s];
		R[i] = G[t];
	}
}

bool solve(int x) {
	for (int i = 1; i <= N; i++) D[i] = (i == x ? 1 : 0);

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++)
			D[R[j]] = max(D[R[j]], D[L[j]] * K[j]);
	}
	return D[x] > 1.0;
}

bool judge () {
	for (int i = 1; i <= N; i++)
		if (solve(i)) return true;
	return false;
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("Case %d: %s\n", cas++, judge() ? "Yes" : "No");
	}
	return 0;
}
