#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N, M, A, B;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int x;
		scanf("%d%d", &N, &M);
		A = B = 0;
		for (int i = 1; i < N; i++) {
			scanf("%d", &x);
			A += x;
		}
		for (int i = 0; i < M; i++) {
			scanf("%d", &x);
			B += x;
		}
		int l = B / M + 1;
		int r = A / (N-1) + (A % (N-1) ? 0 : -1);
		printf("%d %d\n", l, r);
	}
	return 0;
}
