#include <cstdio>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, A, B, x[maxn], v[maxn], r = 0;
map<int, int> G;

bool match (int a, int M, int k) {
	int p = G[a];

	if (!G.count(M - a))
		return false;

	int q = G[M - a];

	if (v[q] == -1 || a * 2 == M) {
		v[p] = v[q] = k;
	} else {

		if (match(A + B - 2 * M + a, M, k))
			v[p] = v[q] = k;
		else
			return false;
	}
	return true;
}

bool solve () {
	if (r >= max(A,B))
		return false;

	for (int i = 1; i <= N; i++) {
		if (v[i] != -1)
			continue;

		if (!match(x[i], A, 0) && !match(x[i], B, 1))
			return false;
	}
	return true;
}

int main () {
	scanf("%d%d%d", &N, &A, &B);
	memset(v, -1, sizeof(v));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &x[i]);
		r = max(x[i], r);
		G[x[i]] = i;
	}

	if (solve()) {
		printf("YES\n");
		for (int i = 1; i <= N; i++)
			printf("%d%c", v[i], i == N ? '\n' : ' ');
	} else
		printf("NO\n");
	return 0;
}
