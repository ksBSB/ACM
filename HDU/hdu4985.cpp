#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int N, f[maxn], v[maxn];

int main () {
	while (scanf("%d", &N) == 1) {
		memset(v, 0, sizeof(v));
		for (int i = 1; i <= N; i++)
			scanf("%d", &f[i]);

		for (int i = 1; i <= N; i++) {
			if (v[i])
				continue;

			printf("(%d", i);
			v[i] = 1;
			for (int j = f[i]; v[j] == 0; j = f[j]) {
				printf(" %d", j);
				v[j] = 1;
			}
			printf(")");
		}
		printf("\n");
	}
	return 0;
}
