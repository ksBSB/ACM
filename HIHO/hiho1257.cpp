#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

char ans[5][100] = { "1 1\n1 1", "1 3\n1 1\n1 2 1 3", "2 3\n1 2\n1 3 2 3\n1 1 2 1 2 2",
					 "2 5\n1 4\n1 5 2 5\n1 1 2 1 2 2\n1 2 1 3 2 3 2 4",
					 "3 4\n1 4 1 5\n2 4 2 5 3 5\n2 2 2 3 3 3 3 2\n3 1 2 1 1 1 1 2 1 3"};

void put(vector<pii>& out) {
	printf("%d %d", out[0].first, out[0].second);
	for (int i = 1; i < out.size(); i++)
		printf(" %d %d", out[i].first, out[i].second);
	printf("\n");
}

void dfs (int r, int c, int d, int n) {
	if (d > n) return;
	vector<pii> out;

	if (d == n) {
		for (int i = 1; i < r; i++) out.push_back(make_pair(i, c));
		for (int i = r-1; i; i--) out.push_back(make_pair(i, c+1));
		put(out);
	} else {
		for (int i = r-2; i; i--) out.push_back(make_pair(i, c));
		for (int i = 1; i <= r; i++) out.push_back(make_pair(i, c+1));
		put(out);

		out.clear();
		for (int i = 1; i <= c; i++) out.push_back(make_pair(r, i));
		out.push_back(make_pair(r-1, c));
		put(out);
	}
	dfs(r + 1, c + 2, d + 2, n);
}

int main () {
	int n;
	while (scanf("%d", &n) == 1) {
		if (n < 5) printf("%s\n", ans[n-1]);
		else {
			int h = (n + 1) >> 1;
			int w = n * (n+1) / 2 / h;
			printf("%d %d\n%s\n", h, w, ans[4]);
			dfs(4, 6, 6, n);
		}
	}
	return 0;
}
