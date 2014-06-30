#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>

using namespace std;
const int N = 1e3+5;
typedef pair<int, int> pi;

int n, m, v[N][N], ans[2*N];

void init() {
	char str[N];
	memset(v, 0, sizeof(v));
	memset(ans, 0, sizeof(ans));

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str+1);
		for (int j = 1; j <= m; j++) {
			if (str[j] == '#') v[i][j] = 0;
			else v[i][j] = v[i-1][j] + 1;
		}
	}
}

void solve () {

	for (int i = 1; i <= n; i++) {
		stack<pi> s;
		for (int j = 1; j <= m; j++) {
			int p = j;
			while (!s.empty() && s.top().first >= v[i][j]) {
				p = s.top().second;
				s.pop();
			}

			if (!v[i][j]) continue;
			if (s.empty() || v[i][j] - s.top().first > p - s.top().second) {
				ans[v[i][j] + j - p + 1]++;
				s.push(make_pair(v[i][j], p));
			} else ans[s.top().first + j - s.top().second + 1]++;
		}
	}
	for (int i = 1; i <= n + m; i++) {
		if (ans[i]) printf("%d x %d\n", ans[i], i * 2);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
