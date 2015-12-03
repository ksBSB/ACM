#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 5005;
const int inf = 0x3f3f3f3f;

int N, M, A[maxn], D[maxn], P[maxn], W[maxn];

void put (int u) {
	if (u == 0) return;
	put(P[u]);
	printf("%d", W[u]);
}

bool bfs () {

	queue<int> que;

	memset(D, 0, sizeof(D));
	for (int i = 0; i < M; i++) {
		if (A[i] == 0) continue;
		int t = A[i] % N;
		P[t] = 0, W[t] = A[i], D[t] = 1;
		que.push(t);
	}

	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (u == 0) {
			put(P[u]);
			printf("%d\n", W[u]);
			return true;
		}

		for (int i = 0; i < M; i++) {
			int v = (u * 10 + A[i]) % N;
			if (!D[v]) {
				D[v] = 1;
				W[v] = A[i];
				P[v] = u;
				que.push(v);
			}
		}
	}
	return false;
}

int main () {
	while (scanf("%d", &N) == 1) {
		scanf("%d", &M);
		int x;
		memset(A, 0, sizeof(A));
		for (int i = 0; i < M; i++)
			scanf("%d", &A[i]);
		sort(A, A + M);
		if (N == 0 || !bfs())
			printf("0\n");
	}
	return 0;
}
