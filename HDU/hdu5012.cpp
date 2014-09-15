#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef int Mat[10];

const int maxn = 100005;
const int INF = 0x3f3f3f3f;
const int dir[4][6] = { {3, 2, 0, 1, 4, 5}, 
						{2, 3, 1, 0, 4, 5},
						{5, 4, 2, 3, 0, 1},
						{4, 5, 2, 3, 1, 0}};

Mat S, E;
int d[maxn];

bool init () {
	for (int i = 0; i < 6; i++)
		if (scanf("%d", &S[i]) != 1)
			return false;
	for (int i  = 0; i < 6; i++)
		if (scanf("%d", &E[i]) != 1)
			return false;

	for (int i = 0; i < 6; i++) {
		S[i]--;
		E[i]--;
	}
	return true;
}

int get_hash(Mat x) {
	int ret = 0;
	for (int i = 0; i < 6; i++)
		ret = ret * 6 + x[i];
	return ret;
}

void reback(int u, Mat a) {
	for (int i = 5; i >= 0; i--) {
		a[i] = u % 6;
		u /= 6;
	}
}

int rotate (int u, int x) {
	Mat a, b;
	reback(u, a);
	for (int i = 0; i < 6; i++)
		b[i] = a[dir[x][i]];
	return get_hash(b);
}

int bfs (int s, int e) {
	memset(d, INF, sizeof(d));

	queue<int> que;
	que.push(s);
	d[s] = 0;

	if (s == e)
		return 0;

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int v = rotate(u, i);

			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				que.push(v);
			}

			if (v == e)
				return d[v];
		}
	}
	return -1;
}

int main () {
	while (init()) {
		printf("%d\n", bfs(get_hash(S), get_hash(E)));
	}
	return 0;
}
