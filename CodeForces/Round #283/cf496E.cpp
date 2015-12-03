#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 5;
typedef pair<int, int> pii;
typedef map<pii, int>::iterator iter;

struct item {
	int l, r, inum, tp;
	item(int l, int r, int inum, int tp) {
		this->l = l;
		this->r = r;
		this->inum = inum;
		this->tp = tp;
	}
	bool operator < (const item& u) const {
		return r > u.r;
	}
};

int N, M, ans[maxn];
priority_queue<item> Act;
map<pii, int> Mp;
vector<item> G;

inline bool cmp(const item& a, const item& b) {
	if (a.l != b.l)
		return a.l < b.l;
	return a.tp < b.tp;
}

void init () {
	int l, r, c;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &l, &r);
		G.push_back(item(l, r, i, inf));
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &l, &r, &c);
		G.push_back(item(l, r, c, i));
	}
	sort(G.begin(), G.end(), cmp);

	/*
	for (int i = 0; i < G.size(); i++)
		printf("%d %d %d %d\n", G[i].tp, G[i].l, G[i].r, G[i].inum);
		*/
}

bool judge() {
	/*
	for (int i = 0; i < G.size(); i++)
		Que.push(G[i]);
	while (!Que.empty()) {
		item tmp = Que.top();
		Que.pop();
		printf("%d %d %d %d\n", tmp.tp, tmp.l, tmp.r, tmp.inum);
	}
	*/

	for (int i = 0; i < G.size(); i++) {
		item& tmp = G[i];

		if (tmp.tp == inf) {
			while (!Act.empty() && Act.top().r < tmp.l) {
				pii u = make_pair(Act.top().r, Act.top().tp);
				Mp.erase(u);
				Act.pop();
			}
			iter it = Mp.lower_bound(make_pair(tmp.r, 0));
			if (it == Mp.end())
				return false;
		//	printf("%d:%d!\n", tmp.inum, it->first.first);
			ans[tmp.inum] = it->first.second;
			it->second--;
			if (it->second == 0) {
		//		printf("cao\n");
				Mp.erase(it);
			}
		} else {
			Mp[make_pair(G[i].r, G[i].tp)] = G[i].inum;
			Act.push(G[i]);
		}
	}
	return true;
}

int main () {
	init();
	if (judge()) {
		printf("YES\n");
		for (int i = 1; i <= N; i++)
			printf("%d%c", ans[i], i == N ? '\n' : ' ');
	} else
		printf("NO\n");
	return 0;
}
