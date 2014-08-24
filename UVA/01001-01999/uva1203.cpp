#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

struct item {
	int num, period, ti;
	bool operator < (const item& a) const {
		return ti > a.ti || (ti == a.ti && num > a.num);
	}
};

int main () {
	priority_queue<item> pri_que;
	char str[105];

	while (scanf("%s", str) == 1 && str[0] != '#') {
		item u;
		scanf("%d%d", &u.num, &u.period);
		u.ti = u.period;;
		pri_que.push(u);
	}

	int Q;
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		item u = pri_que.top();
		pri_que.pop();

		printf("%d\n", u.num);
		u.ti += u.period;
		pri_que.push(u);
	}
	return 0;
}
