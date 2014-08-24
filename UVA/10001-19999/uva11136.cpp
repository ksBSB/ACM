#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

multiset<int> g;

int main () {
	int N, M, x;
	while (scanf("%d", &N) == 1 && N) {
		long long ret = 0;
		g.clear();

		for (int i = 0; i < N; i++) {
			scanf("%d", &M);
			for (int j = 0; j < M; j++) {
				scanf("%d", &x);
				g.insert(x);
			}

			int l = *g.begin(), r = *(--g.end());

			ret += r - l;
			g.erase(--g.end());
			g.erase(g.begin());
		}
		printf("%lld\n", ret);
	}
	return 0;
}
