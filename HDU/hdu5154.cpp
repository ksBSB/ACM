#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, s[maxn], v[maxn];
vector<int> g[maxn];

void init () {
	int a, b;
	memset(s, 0, sizeof(s));
	memset(v, 0, sizeof(v));
	for (int i = 0; i <= N; i++)
		g[i].clear();

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		g[b].push_back(a);
		s[a]++;
	}
}

int find () {
	for (int i = 1; i <= N; i++) {
		if (v[i]) continue;
		if (s[i] == 0)
			return i;
	}
	return 0;
}

bool judge () {
	for (int i = 0; i < N; i++) {
		int u = find();
		if (u == 0)
			return false;

		v[u] = 1;
		for (int j = 0; j < g[u].size(); j++)
			s[g[u][j]]--;
	}
	return true;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
