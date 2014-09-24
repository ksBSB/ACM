#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1005;

int p, q, l, r, v[maxn];
vector<int> g;

void init () {
	int x, y;
	scanf("%d%d%d%d", &p, &q, &l, &r);

	for (int i = 0; i < p; i++) {
		scanf("%d%d", &x, &y);
		for (int j = x; j <= y; j++)
			v[j] = 1;
	}

	for (int i = 0; i < q; i++) {
		scanf("%d%d", &x, &y);
		for (int j = x; j <= y; j++)
			g.push_back(j);
	}
}

bool judge (int t) {
	for (int i = 0; i < g.size(); i++) {
		if (t + g[i] > 1000)
			break;
		if (v[t+g[i]])
			return true;
	}
	return false;
}

int main () {
	init();
	int ret = 0;
	for (int i = l; i <= r; i++) {
		if (judge(i))
			ret++;
	}
	printf("%d\n", ret);
	return 0;
}
