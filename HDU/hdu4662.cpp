#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 3 * 1e6 + 5;

bool vis[maxn];

void presolve() {
	memset(vis, false, sizeof(vis));

	queue<int> que;
	que.push(1);
	vis[1] = true;

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		int d = u - 6;
		if (d >= 0 && vis[d] == false) {
			que.push(d); vis[d] = true;
		}

		d = u * 2;
		if (d < maxn && vis[d] == false) {
			que.push(d); vis[d] = true;
		}
	}
}

char str[maxn];

bool judge () {
	int n = strlen(str), ret = 0;
	if (str[0] != 'M') return false;

	for (int i = 1; i < n; i++) {
		if (str[i] == 'M') return false;
		if (str[i] == 'U') ret += 3;
		if (str[i] == 'I') ret += 1;
	}
	return vis[ret];
}

int main () {
	presolve();
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str);
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}
