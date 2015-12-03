#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, V[maxn], T[maxn];
char S[maxn][maxn];

bool judge (int p) {
	memset(T, 0, sizeof(T));
	for (int i = 1; i < N; i++) {
		if (V[i])
			continue;

		if (S[i][p] < S[i-1][p])
			return true;
		else if (S[i][p] > S[i-1][p])
			T[i] = 1;
	}
	return false;
}

int main () {
	int ans = 0;
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++)
		scanf("%s", S[i]);

	for (int i = 0; i < M; i++) {
		if (judge(i))
			ans++;
		else {
			for (int j = 0; j < N; j++)
				V[j] = V[j] + T[j];
		}
	}
	printf("%d\n", ans);
	return 0;
}
