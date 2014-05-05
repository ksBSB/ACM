#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1<<16;
const int M = 20;

int num[M], v[M], s[N+5];
vector<int> g[N+5];

bool init () {
	memset(s, 0, sizeof(s));
	for (int i = 0; i < N; i++) g[i].clear();

	scanf("%d", &num[0]);
	if (num[0] == 0) return false;
	for (int i = 1; i < 16; i++) scanf("%d", &num[i]);
	sort(num, num + 16);
	return true;
}

bool judge (int k) {
	int cnt = 0;
	for (int i = 0; i < 16; i++) if (k & (1<<i)) {
		v[cnt++] = num[i];
	}
	return cnt == 4;
}

int solve () {
	for (int i = 0; i < N; i++) if (judge(i)) {
		do {
			int cur = v[0] * 4 + v[1] * 3 + v[2] * 2 + v[3];
			for (int j = 0; j < g[cur].size(); j++) if ((i & g[cur][j]) == 0) {
				s[i|g[cur][j]]++;
			}
			g[cur].push_back(i);
		} while (next_permutation(v, v + 4));
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans += s[i] * s[i ^ (N-1)];
	}
	return ans/2;
}

int main () {
	int cas = 1;
	while (init()) {
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
