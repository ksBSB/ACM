#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 10;
int c, si[N*5];

inline int bitCount(int x) {
	return x == 0 ? 0 : bitCount(x/2) + (x&1);
}

void mkdir() {
	c = 0;
	for (int i = 0; i < (1<<5); i++) {
		if (bitCount(i) <= 3)
			si[c++] = i;
	}
}

int n, m, k, ans, g[N][N], tp;

void init () {
	memset(g, 0, sizeof(g));
	ans = 0;
	tp = (1<<m)-1;
	int x, y;
	for (int i = 0; i < k; i++) {
		scanf("%d%d", &x, &y);
		g[x][y] = 1;
	}
}

inline bool judgeSet(int d, int s) {
	for (int i = 0; i < m; i++)
		if ((s&(1<<i)) && g[d][i])
			return false;
	return true;
}

inline void Set(int d, int s, int val) {
	for (int i = 0; i < m; i++)
		if (s&(1<<i))
			g[d][i] = val;
}

inline bool checkup(int x, int y) {
	int flag = 0;
	for (int i = x - 1; i >= 0; i--) {
		if (flag && g[i][y] == 2)
			return true;
		else if (flag && g[i][y] == 1)
			return false;
		else if (g[i][y])
			flag = 1;
	}
	return false;
}

inline bool checklf(int x, int y) {
	int flag = 0;
	for (int i = y - 1; i >= 0; i--) {
		if (flag && g[x][i] == 2)
			return true;
		else if (flag && g[x][i] == 1) 
			return false;
		else if (g[x][i])
			flag = 1;
	}
	return false;
}

bool judgeOk(int d) {
	for (int i = 0; i < m; i++) {
		if (g[d][i] == 2) {
			if (checkup(d, i))
				return false;
			if (checklf(d, i))
				return false;
		}
	}
	return true;
}

void dfs(int d, int cnt) {

	if (ans >= (n-d)*3+cnt)
		return;

	if (d >= n) {
		ans = max(ans, cnt);
		return;
	}

	for (int i = 0; i < c; i++) {

		if (si[i] > tp)
			continue;

		if (judgeSet(d, si[i])) {
			Set(d, si[i], 2);

			if(judgeOk(d)) {
				dfs(d+1, cnt + bitCount(si[i]));
			}

			Set(d, si[i], 0);
		}
	}
}

int main () {
	mkdir();
	while (scanf("%d%d%d", &n, &m, &k) == 3) {
		init();
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
