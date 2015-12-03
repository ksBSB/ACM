#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 505;
const int maxm = 2005;

int N, F[maxn];
char str[maxn][maxm];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%s", str[i]);

		int p = N-1;
		while (p && strstr(str[p], str[p-1]) != NULL) p--;
		p++;

		for (int i = p-2; i >= 0 && p < N; i--) {
			while (p < N && strstr(str[p], str[i]) == NULL) p++;
		}
		if (p == 1) p = -1;
		printf("Case #%d: %d\n", kcas, p);
	}
	return 0;
}
