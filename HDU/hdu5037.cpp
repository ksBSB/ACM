#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, L;
vector<int> g;

void init () {
	int x;
	g.clear();
	scanf("%d%d%d", &N, &M, &L);
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);
		g.push_back(x);
	}
	g.push_back(0);
	g.push_back(M);
	sort(g.begin(), g.end());
}

int solve () {
	int ret = 0;
	int pos = 0, mv = 0;

	while (true) {
		int idx = upper_bound(g.begin(), g.end(), pos + L) - g.begin() - 1;

		if (g[idx] <= pos) {

			int k = (g[idx+1] - pos) / (L + 1);

			if (k == 1) {
				ret++;
				int tmp = mv + 1;
				mv = pos + L;
				pos = tmp;
			} else {
				k--;
				ret += k * 2;
				pos = pos + k * (L + 1);
				mv = mv + k * (L + 1);
			}

		} else {
			mv = pos + L;
			pos = g[idx];
			ret++;
		}

		if (pos == M)
			break;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
