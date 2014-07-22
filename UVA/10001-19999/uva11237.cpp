#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100000;
int a[maxn+5], s[maxn+5], vis[maxn+5];

int main () {
	int c, n;
	while (scanf("%d%d", &c, &n) == 2 && c + n) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		memset(vis, -1, sizeof(vis));

		vis[0] = s[0] = 0;
		for (int i = 1; i <= n; i++) {
			s[i] = (s[i-1] + a[i]) % c;

			if (vis[s[i]] == -1)
				vis[s[i]] = i;
			else {
				for (int j = vis[s[i]] + 1; j <= i; j++)
					printf("%d%c", j, j == i ? '\n' : ' ');
				break;
			}
		}
	}
	return 0;
}
