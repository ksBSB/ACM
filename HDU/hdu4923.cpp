#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int n, a[maxn], l, r;

struct state {
	int p, q;
	double x;
	state (int p, int q) {
		this->p = p;
		this->q = q;
		this->x = p * 1.0 / (p + q);
	}
};

double solve () {
	l = 0; r = n-1;
	while (l < n && a[l] == 0)
		l++;
	while (r >= 0 && a[r] == 1)
		r--;

	if (r <= l)
		return 0;

	bool flag = true;
	int cntp = 0, cntq = 0;
	queue<state> que;

	for (int i = l; i <= r; i++) {
		if (flag && a[i] == 1)
			cntp++;
		else if (flag == false && a[i] == 0)
			cntq++;
		else if (flag == false && a[i] == 1) {
			que.push(state(cntp, cntq));
			cntp = 1;
			flag = true;
		} else {
			cntq = 1;
			flag = false;
		}
	}

	que.push(state(cntp, cntq));

	stack<state> sta;
	while (!que.empty()) {
		state u = que.front();
		que.pop();

		while (!sta.empty() && sta.top().x > u.x) {
			u.p += sta.top().p;
			u.q += sta.top().q;
			u.x = u.p * 1.0 / (u.p + u.q);
			sta.pop();
		}

		sta.push(u);
	}

	double ans = 0;
	while (!sta.empty()) {
		state u = sta.top();	
		sta.pop();
		ans += (pow(1-u.x, 2) * u.p + pow(u.x, 2) * u.q);
	}
	return ans;;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		printf("%.6lf\n", solve());
	}
	return 0;
}
