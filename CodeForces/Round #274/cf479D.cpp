#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5+5;
int N, L,  X, Y, A[maxn];

bool judge (int u) {
	if (u < 0 || u > L) return false;
	int k = lower_bound(A, A + N, u) - A;
	return u == A[k];
}

void solve () {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (judge(A[i] - X) || judge(A[i] + X))
			ans |= 1;
		if (judge(A[i] - Y) || judge(A[i] + Y))
			ans |= 2;
	}

	if (ans == 3)
		printf("0\n");
	else if (ans == 2)
		printf("1\n%d\n", X);
	else if (ans == 1)
		printf("1\n%d\n", Y);
	else {

		for (int i = 0; i < N; i++) {
			int tx = A[i] + X;
			int ty = A[i] + Y;

			if (tx <= L && (judge(tx - Y) || judge(tx + Y))) {
				printf("1\n%d\n", tx);
				return;
			}

			if (ty <= L && (judge(ty - X) || judge(ty + X))) {
				printf("1\n%d\n", ty);
				return;
			}
		}

		for (int i = 0; i < N; i++) {
			int tx = A[i] - X;
			int ty = A[i] - Y;

			if (tx >= 0 && (judge(tx - Y) || judge(tx + Y))) {
				printf("1\n%d\n", tx);
				return;
			}

			if (ty >= 0 && (judge(ty - X) || judge(ty + X))) {
				printf("1\n%d\n", ty);
				return;
			}
		}
		printf("2\n%d %d\n", X, Y);
	}
}

int main () {
	scanf("%d%d%d%d", &N, &L, &X, &Y);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	solve();
	return 0;
}
