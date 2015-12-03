#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100005;
const int maxm = 20;

int N, A[maxn], mx[maxn][maxm+5], mi[maxn][maxm+5];

int query(int l, int r) {
	int k = 0;
	while ((1<<(k+1)) <= r - l + 1)
		k++;
	return max(mx[l][k], mx[r-(1<<k)+1][k]) - min(mi[l][k], mi[r-(1<<k)+1][k]);
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

	for (int i = 1; i <= N; i++)
		mx[i][0] = mi[i][0] = A[i];

	for (int j = 1; (1<<j) <= N; j++) {
		for (int i = 1; i + (1<<j) - 1 <= N; i++) {
			mi[i][j] = min(mi[i][j-1], mi[i + (1<<(j-1))][j-1]);
			mx[i][j] = max(mx[i][j-1], mx[i + (1<<(j-1))][j-1]);
		}
	}
}

int main () {
	init();

	int l = 1, r = 1, ans = 1;
	while (l <= N) {
		while (r <= N && query(l, r) <= 1) r++;
		ans = max(r - l, ans);
		l++;
	}
	printf("%d\n", ans);
	return 0;
}
