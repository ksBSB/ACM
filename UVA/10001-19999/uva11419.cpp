#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;

int R, C, N, L[maxn];
bool S[maxn], T[maxn], V[maxn];
vector<int> G[maxn];

bool match(int u) {
	S[u] = true;
	for (int i = 0; i < G[u].size(); i++) {
		int j = G[u][i];
		if (!T[j]) {
			T[j] = true;
			if (!L[j] || match(L[j])) {
				L[j] = u;
				return true;
			}
		}
	}
	return false;
}

int KM () {
	int ret = 0;
	memset(L, 0, sizeof(L));

	for (int i = 1; i <= R; i++) {
		memset(S, false, sizeof(S));
		memset(T, false, sizeof(T));
		if (match(i)) ret++;
	}
	return ret;
}

int main () {
	while (scanf("%d%d%d", &R, &C, &N) == 3 && R + C + N) {
		for (int i = 1; i <= R; i++) G[i].clear();
		int u, v;
		while (N--) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		printf("%d", KM());
		memset(S, false, sizeof(S));
		memset(T, false, sizeof(T));
		memset(V, false, sizeof(V));
		for (int i = 1; i <= C; i++) V[L[i]] = true;
		for (int i = 1; i <= R; i++) if (!V[i])
			match(i);
		for (int i = 1; i <= R; i++) if (!S[i])
			printf(" r%d", i);
		for (int i = 1; i <= C; i++) if (T[i])
			printf(" c%d", i);
		printf("\n");
	}
	return 0;
}
