#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef pair<int, int> pii;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

const int maxn = 100005;
const ull X = 107;

char str[maxn];
int N, M;
vector<pii> ans;
ull G[12][maxn], H[maxn], T[maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < 4; i++) {
		scanf("%s", str+1);

		G[lson(i)][N+1] = G[rson(i)][N+1] = 0;
		for (int j = N; j >= 1; j--) {
			G[lson(i)][j] = G[lson(i)][j+1] * X + (str[j] - 'a');
			G[rson(i)][j] = G[rson(i)][j+1] * X + (str[N-j+1] - 'a');
		}
	}

	scanf("%s", str+1);
	H[M+1] = 0;
	for (int j = M; j >= 1; j--)
		H[j] = H[j+1] * X + (str[j] - 'a');
}

bool dfs (int k, int pos, int dir, int L) {
	if (L == 0)
		return true;

	int len = min(N - pos + 1, L);
	if (G[(k<<1)|dir][pos] - G[(k<<1)|dir][pos+len] * T[len] == H[M-L+1] - H[M-L+len+1] * T[len]) {
		ans.push_back(make_pair(k * N + (dir ? N + 1 - pos : pos), dir));
		L -= len;

		if (L == 0)
			return true;

		for (int i = 0; i < 4; i++) {
			for (int d = 0; d < 2; d++) {
				if (k == i && (d^1) == dir)
					continue;

				if (dfs(i, 1, d, L))
					return true;
			}
		}

		ans.pop_back();
	}

	return false;
}

bool solve () {
	for (int i = 0; i < 4; i++) {
		for (int pos = 1; pos <= N; pos++) {
			for (int d = 0; d < 2; d++) {
				ans.clear();
				if (dfs(i, pos, d, M))
					return true;
			}
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);

	T[0] = 1;
	for (int i = 1; i < maxn; i++)
		T[i] = T[i-1] * X;

	while (cas--) {
		init();
		if (solve()) {

			int p = 0;
			for (int k = 0; k < ans.size(); k++) {
				int u = (ans[k].first - 1) / N + 1, dir = ans[k].second;

				if (dir == 0) {
					for (int i = ans[k].first; i <= u * N && p < M; i++, p++) {
						if (p) printf(" ");
						printf("%d", i);
					}
				} else {
					for (int i = ans[k].first; i > (u-1) * N && p < M; i--, p++) {
						if (p) printf(" ");
						printf("%d", i);
					}
				}
			}
			printf("\n");
		} else
			printf("No solution!\n");
	}
	return 0;
}
