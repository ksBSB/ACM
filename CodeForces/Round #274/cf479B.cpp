#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 1e5;

int N, K, A[maxn], X[maxn], Y[maxn], pMax, pMin;

void find () {
	pMax = pMin = 0;
	int vMax = 0, vMin = inf;
	for (int i = 1; i <= N; i++) {
		if (A[i] > vMax) {
			vMax = A[i];
			pMax = i;
		}

		if (A[i] < vMin) {
			vMin = A[i];
			pMin = i;
		}
	}
}

int solve() {
	find();
	for (int i = 0; i < K; i++) {
		if (A[pMax] - A[pMin] <= 1)
			return i;
		X[i] = pMax;
		Y[i] = pMin;
		A[pMax]--; A[pMin]++;
		find();
	}
	return K;
}

int main () {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	int ans = solve();
	printf("%d %d\n", A[pMax] - A[pMin], ans);
	for (int i = 0; i < ans; i++)
		printf("%d %d\n", X[i], Y[i]);
	return 0;
}
