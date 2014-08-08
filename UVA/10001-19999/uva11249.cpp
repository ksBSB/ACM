#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5;

int N, K, v[maxn+5];

void init () {
	memset(v, -1, sizeof(v));

	int mv = 0;
	v[0] = 0;

	for (int i = 1; i <= maxn; i++) {
		if (v[i] == -2)
			continue;

		int tmp = v[mv] + i - mv + K + 1;
		if (tmp > maxn)
			break;

		v[i] = tmp;
		v[tmp] = -2;
		mv = i;
	}
}

int main () {
	int cas, a, b;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &K, &N);
		init();

		for (int i = 0; i < N; i++) {
			scanf("%d%d", &a, &b);
			int p = min(a, b);
			int q = max(a, b);
			printf("%s\n", v[p] == q ? "LOSING" : "WINNING");
		}
		printf("\n");
	}
	return 0;
}
