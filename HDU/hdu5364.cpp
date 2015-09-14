#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;

int N, M, A, C[maxn], T[maxn];

int main () {
	while (scanf("%d", &N) == 1) {
		M = -1;
		memset(C, 0, sizeof(C));

		for (int i = 0; i < N; i++) {
			scanf("%d", &A);
			C[A]++;
		}

		for (int i = 0; i < maxn; i++) {
			if (C[i] > N - C[i])
				T[++M] = i;
		}
		
		for (int i = 0; i <= M; i++)
			printf("%d%c", T[i], i == M ? '\n' : ' ');
		if (M == -1)
			printf("-1\n");
	}
	return 0;
}
