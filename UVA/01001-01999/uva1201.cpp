#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 505;

int N, L[maxn], K[maxn];
vector<int> G[maxn];
bool S[maxn], T[maxn];

struct Point {
	int x, y;
	void read() { scanf("%d%d", &x, &y); }
}A[maxn], B[maxn];

int dis(Point a, Point b) {
	return abs(a.x-b.x) + abs(a.y-b.y);
}

bool judge (int a, int b) {
	int last = K[a] + dis(B[a], A[a]) + dis(A[b], B[a]);
	return last < K[b];
}

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

	for (int i = 1; i <= N; i++) {
		memset(S, false, sizeof(S));
		memset(T, false, sizeof(T));
		if (match(i)) ret++;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		int h, m;
		for (int i = 1; i <= N; i++) {
			G[i].clear();
			scanf("%d:%d", &h, &m);
			K[i] = h * 60 + m;
			A[i].read(), B[i].read();
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) if (i != j && judge(i, j))
				G[i].push_back(j);
		}
		printf("%d\n", N - KM());
	}
	return 0;
}
