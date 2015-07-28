#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100000 + 5;
const int maxm = 20;

int N, K, A[maxn], dMax[maxn][maxm], dMin[maxn][maxm];

void RmqInit() {
	for (int i = 0; i < N; i++)
		dMax[i][0] = dMin[i][0] = A[i];
	for (int j = 1; (1<<j) <= N; j++) {
		for (int i = 0; i + (1<<j) - 1 < N; i++) {
			dMax[i][j] = max(dMax[i][j-1], dMax[i + (1<<(j-1))][j-1]);
			dMin[i][j] = min(dMin[i][j-1], dMin[i + (1<<(j-1))][j-1]);
		}
	}
}

int RmqQuery(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r - l + 1)
		k++;
	return max(dMax[l][k], dMax[r-(1<<k)+1][k]) - min(dMin[l][k], dMin[r-(1<<k)+1][k]);
}

void init () {
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	RmqInit();
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int l = 0;
		long long ans = 0;
		for (int i = 0; i < N; i++) {
			while (RmqQuery(l, i) >= K)
				l++;
			ans += i - l + 1;
		}
		printf("%lld\n", ans);
	}

	return 0;
}
