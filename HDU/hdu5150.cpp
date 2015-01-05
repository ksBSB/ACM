#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 1000;
int vis[maxn + 5];

void init (int n) {
	memset(vis, 0, sizeof(vis));
	vis[1] = 0;
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

int main () {
	init(maxn);
	int n;
	while (scanf("%d", &n) == 1) {
		int ans = 0, x;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			if (vis[x] == 0)
				ans += x;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
