#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int N = 105;
const int INF = 0x3f3f3f3f;

int n, m;

bool judge() {
	if (n >= 50) return true;

	queue<int> q;
	int u, v, d[N];
	memset(d, INF, sizeof(d));
	d[1] = 1;
	q.push(1);

	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == m) return true;
		v = u + d[u] + 2;
		if (v <= n) {
			q.push(v); d[v] = d[u] + 2;
		}

		v = u - d[u] - 2;
		if (v > 0) {
			q.push(v); d[v] = d[u] + 2;
		}
	}
	return false;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		printf("%s\n", judge() ? "Let me try!" : "Don't make fun of me!");
	}
	return 0;
}
