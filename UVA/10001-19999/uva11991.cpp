#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
map<int, vector<int> > g;

int main () {
	int N, M, x, y;
	while (scanf("%d%d", &N, &M) == 2) {
		g.clear();
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			if (!g.count(x))
				g[x] = vector<int>();
			g[x].push_back(i);
		}
		
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &x, &y);
			if (!g.count(y) || g[y].size() < x)
				printf("0\n");
			else
				printf("%d\n", g[y][x-1]);
		}
	}
	return 0;
}
