#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1e7;
const int INF = 0x3f3f3f3f;

#define lowbit(x) ((x)&(-x))

int N, size[50], c[50];
int pos[maxn+5], fenx[maxn+5];

struct point {
	int val, mac;
	point (int val = 0, int mac = 0) {
		this->val = val;
		this->mac = mac;
	}
};

queue<int> que;
vector<point> vec;

inline bool cmp (const point& a, const point& b) {
	if (a.val != b.val)
		return a.val < b.val;
	return a.mac < b.mac;
}

int sum (int x) {
	int ret = 0;
	while (x) {
		ret += fenx[x];
		x -= lowbit(x);
	}
	return ret;
}

void add (int x, int v) {
	while (x <= maxn) {
		fenx[x] += v;
		x += lowbit(x);
	}
}

int get_distance (int i) {
	if (pos[i] == -INF)
		return INF;
	return i - pos[i] - sum(i) + sum(pos[i] - 1);
}

void hit (int i) {
	if (i <= 0)
		return;
	add(i, 1);
}

void put_ans() {
	for (int i = 1; i <= N; i++)
		printf("%d%c", c[i], i == N ? '\n' : ' ');
	memset(c, 0, sizeof(c));
}

void solve () {
	memset(c, 0, sizeof(c));
	memset(fenx, 0, sizeof(fenx));

	int n = vec.size();
	sort(vec.begin(), vec.end(), cmp);


	if (que.front() == 0) {
		put_ans();
		que.pop();
	}

	if (n == 0)
		return;
	pos[vec[0].mac] = -INF;
	for (int i = 1; i < n; i++) {
		if (vec[i].val == vec[i-1].val)
			pos[vec[i].mac] = vec[i-1].mac;
		else
			pos[vec[i].mac] = -INF;
	}

	for (int i = 1; i <= n; i++) {
		int dist = get_distance(i);
		int mv = 1;

		while (mv <= N && size[mv] < dist) {
			c[mv]++;
			mv++;
		}

		while (i == que.front()) {
			put_ans();

			que.pop();
			if (que.empty())
				break;
		}
		hit(pos[i]);
	}

	while (!que.empty())
		que.pop();
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &size[i]);

		vec.clear();
		int x, y, n;
		char order[50];
		while (scanf("%s", order) == 1 && strcmp(order, "END")) {
			if (order[0] == 'R') {
				scanf("%d%d%d", &x, &y, &n);
				for (int i = 0; i < n; i++)
					vec.push_back(point(x + y * i, vec.size() + 1));
			} else if (order[0] == 'A') {
				scanf("%d", &x);
				vec.push_back(point(x, vec.size() + 1));
			} else
				que.push(vec.size());
		}
		solve();
	}
	return 0;
}
