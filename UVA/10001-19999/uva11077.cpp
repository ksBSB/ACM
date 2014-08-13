#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 21;

ll f[maxn+5][maxn+5];

int main () {
	memset(f, 0, sizeof(f));
	f[1][0] = 1;
	for (int i = 2; i <= maxn; i++) {
		for (int j = 0; j < i; j++) {
			f[i][j] = f[i-1][j];
			if (j)
				f[i][j] += f[i-1][j-1] * (i-1);
		}
	}

	int n, k;
	while (scanf("%d%d", &n, &k) == 2 && n + k) {
		printf("%llu\n", f[n][k]);
	}
	return 0;
}
