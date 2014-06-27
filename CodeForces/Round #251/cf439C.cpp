#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1e5 + 5;

int n, k, p, d[N];
vector<int> g[N];

inline bool cmp (const int& a, const int& b) {
	return (a&1) > (b&1);
}

void init () {
	scanf("%d%d%d", &n, &k, &p);
	for (int i = 0; i < n; i++)
		scanf("%d", &d[i]);

	sort(d, d + n, cmp);
	for (int i = 0; i < k; i++)
		g[i].clear();
}

bool judge () {
	int mv = 0;
	for (int i = 0; i < k - p; i++) {
		if (d[mv]&1)
			g[i].push_back(d[mv++]);
		else
			return false;
	}

	int t = k - p;
	while (mv < n) {

		t %= k;

		if (d[mv]&1) {
			g[t].push_back(d[mv++]);

			if ((d[mv]&1) != 1 || mv >= n)
				return false;

			g[t].push_back(d[mv++]);
		} else {
			g[t].push_back(d[mv++]);
		}
		t++;
	}

	if (g[k-1].size() == 0)
		return false;
	return true;
}

int main () {
	init();

	if (judge()) {
		printf("YES\n");
		for (int i = 0; i < k; i++) {
			printf("%lu", g[i].size());
			for (int j = 0; j < g[i].size(); j++)
				printf(" %d", g[i][j]);
			printf("\n");
		}
	} else
		printf("NO\n");

	return 0;
}
