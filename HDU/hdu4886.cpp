#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1000005;

int n, f[10], vis[maxn];
char str[maxn];

bool solve (int k) {
	memset(vis, 0, sizeof(vis));
	int tmp = 0;
	for (int i = 0; i < k; i++)
		tmp = tmp * 8 + str[i] - 'A';

	vis[tmp] = 1;
	for (int i = k; i < n; i++) {
		tmp = tmp % f[k-1];
		tmp = tmp * 8 + str[i] - 'A';
		vis[tmp] = 1;
	}

	int x = 0;
	while (vis[x]) x++;

	if (x < f[k]) {
		for (int i = k-1; i >= 0; i--) {
			printf("%c", x / f[i] + 'A');
			x %= f[i];
		}
		printf("\n");
		return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	f[0] = 1;
	for (int i = 1; i <= 8; i++)
		f[i] = f[i-1] * 8;

	while (cas--) {
		scanf("%s", str);
		n = strlen(str);
		for (int i = 1; !solve(i); i++);
	}
	return 0;
}
