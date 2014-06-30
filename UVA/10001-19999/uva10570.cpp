#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int N =  505;
int n, num[ N * 2];

void rechange(int c[]) {
	int tmp;
	int d = n / 2;
	for (int i = 1; i <= d; i++) {
		tmp = c[i];
		c[i] = c[n - i + 1];
		c[n - i + 1] = tmp;
	}
}

int find(int c[]) {
	int tmp = 0, vis[N];
	memset(vis, 0, sizeof(vis));

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			tmp++;
			for (int x = i; !vis[x]; x = c[x]) vis[x] = 1;
		}
	}
	return n - tmp;
}

int solve() {
	int ans = 1 << 30;

	for (int i = 1; i <= n; i++) num[i + n] = num[i];
	for (int i = 1; i <= n; i++) ans = min(ans, find(num + i));
	rechange(num);
	for (int i = 1; i <= n; i++) num[i + n] = num[i];
	for (int i = 1; i <= n; i++) ans = min(ans, find(num + i));
	return ans;
}

int main () {
	while (scanf("%d", &n),  n) {
		for (int i = 1;  i <= n; i++) scanf("%d", &num[i]);
		printf("%d\n", solve());
	}
	return 0;
}
