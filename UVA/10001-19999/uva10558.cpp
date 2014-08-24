#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;

struct item {
	int ti, pos, id;
	item (int ti = 0, int id = 0, int pos = 0) {
		this->ti = ti;
		this->id = id;
		this->pos = pos;
	}

	bool operator < (const item& u) const {
		return ti > u.ti || (ti == u.ti && id > u.id);
	}
};

int N, M;
vector<int> g[maxn];
priority_queue<item> que[maxn];

void init () {
	int t, k, x;
	scanf("%d%d", &N, &M);

	for (int i = 1; i <= N; i++) {
		g[i].clear();
		scanf("%d%d", &t, &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &x);
			g[i].push_back(x);
		}
		que[g[i][0]].push(item(t, i, 0));
	}
}

int solve () {
	int ret = 0;
	bool flag = true;
	while (flag) {
		flag = false;

		for (int i = 1; i <= M; i++) {
			if (que[i].empty())
				continue;

			flag = true;
			item u = que[i].top();

			if (u.ti > ret)
				continue;

			que[i].pop();

			if (u.pos + 1 >= g[u.id].size())
				continue;

			int next = g[u.id][u.pos+1];
			que[next].push(item(ret+1, u.id, u.pos+1));
		}
		ret++;
	}
	return ret - 1;
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
