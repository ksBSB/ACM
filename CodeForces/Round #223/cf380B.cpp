#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>

using namespace std;
const int N = 7005;
const int M = 200000;

struct state {
	int l, r, val;
	state() {}
	state(int l, int r, int val) {
		this->l = l; this->r = r; this->val = val;
	}
};

int n, m, dl[M], dr[M];
vector<state> v[N];

int solve (int d, int x, int y) {
	set<int> ans;

	for (int i = d; i <= n; i++) {
		for (int j = 0; j < v[i].size(); j++) {
			state& c = v[i][j];
			if (c.l <= y && c.r >= x) ans.insert(c.val);
		}

		x = (dl[x] == -1 ? dr[x] : dl[x]);
		y = dr[y];
	}
	return ans.size();	
}

void init () {
	int cnt = 1, p = 3;
	memset(dl, -1, sizeof(dl));
	memset(dr, -1, sizeof(dr));
	dl[1] = 1; dr[1] = 2;
	for (int i = 2; i < M; i++) {
		if ((1<<cnt) == i) {
			cnt++;
			dl[i] = p++;
		}
		dr[i] = p++;
	}
}

int main () {
	init ();
	int order, d, x, y, val;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &order);
		if (order == 1) {
			scanf("%d%d%d%d", &d, &x, &y, &val);
			v[d].push_back(state(x, y, val));
		} else {
			scanf("%d%d", &d, &x);
			printf("%d\n", solve(d, x, x));
		}
	}
	return 0;
}
