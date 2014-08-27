#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int N, Q, num[maxn], rmq[maxn][20];
int left[maxn], right[maxn];

void RMQ_init () {
	memset(rmq, 0, sizeof(rmq));
	for (int i = 1; i <= N; i++)
		rmq[i][0] = right[i] - left[i] + 1;

	for (int j = 1; (1<<j) <= N; j++) {
		for (int i = 1; i + (1<<j) - 1 <= N; i++)
			rmq[i][j] = max(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
	}
}

void init () {
	for (int i = 1; i <= N; i++)
		scanf("%d", &num[i]);

	left[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (num[i] == num[i-1])
			left[i] = left[i-1];
		else
			left[i] = i;
	}

	right[N] = N;
	for (int i = N-1; i >= 1; i--) {
		if (num[i] == num[i+1])
			right[i] = right[i+1];
		else
			right[i] = i;
	}
	RMQ_init();
}

int RMQ (int L, int R) {
	if (L > R)
		return 0;
	int k = 0;
	while (1<<(k+1) <= R-L+1)
		k++;
	return max(rmq[L][k], rmq[R-(1<<k)+1][k]);
}

int main () {
	while (scanf("%d%d", &N, &Q) == 2 && N) {
		init();
		int x, y;
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &x, &y);
			if (num[x] == num[y])
				printf("%d\n", y - x + 1);
			else
				printf("%d\n", max(RMQ(right[x]+1, left[y]-1), max(right[x] - x + 1, y - left[y] + 1)));
		}
	}
	return 0;
}
