#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 505;

int N, K, C[maxn];

bool judge () {

	for (int i = 1; i <= N; i++) {
		if (C[i] == 0)
			return false;

		if (i + K <= N)
			C[i+K] += C[i] - 1;
	}
	return true;
}

int main () {
	int cas, x;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &K);
		memset(C, 0, sizeof(C));
		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			C[x]++;
		}

		printf("%s\n", judge() ? "Jerry" : "Tom");
	}
	return 0;
}
