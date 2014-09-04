#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int jump[maxn], c[maxn];

void get_jump (char* s, int n) {
	int p = 0;
	jump[0] = jump[1] = 0;
	for (int i = 2; i <= n; i++) {
		while (p && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;

		jump[i] = p;
	}
}

int main () {
	int cas;
	char s[maxn];
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", s+1);

		int n = strlen(s+1);
		memset(c, 0, sizeof(c));

		for (int t = 0; t < n; t++) {
			int m = n - t;
			get_jump(s + t, m);

			for (int j = 1; j <= m; j++) {
				int p = j;
				while (p) {

					p = jump[p];
					if (j % (j - p) == 0) {
						int k = j / (j - p);
						c[k] = max(c[k], j);
					}
				}
			}
		}

		printf("Case #%d:", kcas);
		for (int i = 1; i <= n; i++)
			printf(" %d", c[i]);
		printf("\n");
	}
	return 0;
}
