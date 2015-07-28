#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e6;

int F[maxn + 5], C[maxn + 5][10];

void init () {
	memset(F, 0, sizeof(F));
	for (int i = 2; i <= maxn; i++) {
		if (F[i]) continue;
		for (int j = i; j <= maxn; j += i)
			F[j]++;
	}

	memset(C[1], 0, sizeof(C[1]));
	for (int i = 2; i <= maxn; i++) {
		memcpy(C[i], C[i-1], sizeof(C[i]));
		C[i][F[i]]++;
	}
}

int main () {
	init();
	int t, l, r, c[10];
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d%d", &l, &r);

		int ans = 1;
		for (int j = 2; j <= 7; j++) {
			c[j] = C[r][j] - C[l-1][j];
			if (c[j] >= 2)
				ans = max(ans, j);
		}

		if (c[3] + c[6] >= 2)
			ans = max(ans, 3);
		if (c[2] + c[4] + c[6] >= 2)
			ans = max(ans, 2);
		printf("%d\n", ans);
	}
	return 0;
}
