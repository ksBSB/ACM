#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;

int N, K, G[maxn][maxn], C[maxn];
vector<pii> s;

void solve(int l, int r, int k) {
	s.clear();
	for (int i = 0; i < N; i++) if (i != k)
		s.push_back(make_pair(C[i], i));
	sort(s.begin(), s.end());

	for (int i = l; i <= r; i++) {
		int t = (i - l) % (N-1);
		G[i][1] = s[t].second;
	}
}

void draw(int* x) {
	int p = 2;
	for (int i = 0; i < N; i++) {
		if (i == x[0] || i == x[1]) continue;
		x[p++] = i;
	}
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		memset(C, 0, sizeof(C));
		int t = K / N, f = K % N, p = 0;

		for (int i = 0; i < f; i++) {
			for (int j = 0; j < t + 1; j++)
				G[p++][0] = i;
			C[i] = t + 1;
		}
		for (int i = f; i < N; i++) {
			for (int j = 0; j < t; j++)
				G[p++][0] = i;
			C[i] = t;
		}

		p = 0;
		for (int i = 0; i < K; i++) {
			if (G[i][0] != G[p][0]) {
				solve(p, i - 1, G[p][0]);
				p = i;
			}
		}
		solve(p, K-1, G[p][0]);

		for (int i = 0; i < K; i++) {
			draw(G[i]);
			for (int j = 0; j < N; j++)
				printf("%d%c", G[i][j] + 1, j == N-1 ? '\n' : ' ');
		}
	}
	return 0;
}
