#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M, A[maxn], B[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++) scanf("%d", &A[i]);
		for (int i = 0; i < N; i++) scanf("%d", &B[i]);

		sort(A, A + N);
		sort(B, B + N);
		int sa = 0, sb = 0;
		for (int i = 0; i < M; i++) {
			sa += A[i];
			sb += B[N-i-1];
		}
		printf("%s\n", sa > sb ? "YES" : "NO");
	}
	return 0;
}
