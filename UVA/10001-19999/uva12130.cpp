#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 505;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct point {
	int x, y, val;
	point (int x = 0, int y = 0, int val = 0) {
		this->x = x;
		this->y = y;
		this->val = val;
	}
	bool operator < (const point& u) const {
		return val > u.val;
	}
};

int N, M, D, g[maxn][maxn], v[maxn][maxn];
vector<point> vec;

void init () {
	vec.clear();

	memset(v, 0, sizeof(v));
	scanf("%d%d%d", &N, &M, &D);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &g[i][j]);
			vec.push_back(point(i, j, g[i][j]));
		}
	}
	sort(vec.begin(), vec.end());
}

int bfs (int x, int y, int h) {
	int ret = 1;
	bool flag = true;
	queue<point> que;
	que.push(point(x, y));

	while (!que.empty()) {
		point u = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int p = u.x + dir[i][0];
			int q = u.y + dir[i][1];

			if (p <= 0 || p > N || q <= 0 || q > M)
				continue;

			if (h - g[p][q] >= D)
				continue;

			if (v[p][q] > h) {
				flag = false;
				continue;
			}

			if (v[p][q] == h)
				continue;

			if (g[p][q] == h)
				ret++;
			v[p][q] = h;
			que.push(point(p, q));
		}
	}
	//printf("%d %d %d %d\n", x, y, g[x][y], ret);

	if (flag == false)
		return 0;
	return ret;
}

int solve () {
	int ret = 0;
	for (int i = 0; i < vec.size(); i++) {
		int x = vec[i].x, y = vec[i].y;
		if (v[x][y])
			continue;
		v[x][y] = g[x][y];
		ret += bfs(x, y, g[x][y]);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
