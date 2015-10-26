#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M, L[maxn], X[maxn], Y[maxn];
bool T[maxn];
vector<int> G[maxn];

bool match(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!T[v]) {
			T[v] = true;
			if (!L[v] || match(L[v])) {
				L[v] = u;
				return true;
			}
		}
	}
	return false;
}

int KM () {
	int ret = 0;
	memset(L, 0, sizeof(L));
	for (int i = 1; i <= M; i++) {
		memset(T, false, sizeof(T));
		if (match(i))
			ret++;
	}
	return ret;
}

void init () {
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &X[i], &Y[i]);

	int x, y;
	for (int i = 1; i <= M; i++) {
		G[i].clear();
		scanf("%d%d", &x, &y);
		for (int j = 1; j <= N; j++) {
			if ((x == X[j] || x == X[j]+1) && 
					(Y[j] == y || Y[j] == y+1)) {
				G[i].push_back(j);
			}
		}
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("%d\n", N + M - KM());
	}
	return 0;
}
