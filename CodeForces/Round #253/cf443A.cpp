#include <cstdio>
#include <cstring>

const int N = 1005;

int n, v[N];
char s[N];

int main () {
	int ans = 0;
	memset(v, 0, sizeof(v));

	gets(s);
	n = strlen(s);

	for (int i = 0; i < n; i++) {
		if (s[i] >= 'A' && s[i] <= 'z') {
			int u = s[i] - 'A';

			if (v[u] == 0)
				ans++;
			v[u] = 1;
		}
	}
	printf("%d\n", ans);

	return 0;
}
