#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100005;
const int SIGMA_SIZE = 11;
const int mod = 2012;

struct SAM {
	int sz, last;
	int g[maxn<<1][SIGMA_SIZE], pre[maxn<<1], step[maxn<<1];


	void newNode (int s) {
		step[++sz] = s;
		pre[sz] = 0;
		memset(g[sz], 0, sizeof(g[sz]));
	}

	void init () {
		sz = 0, last = 1;
		newNode(0);
	}

	void insert(int v) {
		newNode(step[last] + 1);
		int p = last, np = sz;

		while (p && !g[p][v]) {
			g[p][v] = np;
			p = pre[p];
		}

		if (p) {
			int q = g[p][v];
			if (step[q] == step[p] + 1)
				pre[np] = q;
			else {
				newNode(step[p] + 1);
				int nq = sz;
				for (int j = 0; j < SIGMA_SIZE; j++) g[nq][j] = g[q][j];

				pre[nq] = pre[q];
				pre[np] = pre[q] = nq;

				while (p && g[p][v] == q) {
					g[p][v] = nq;
					p = pre[p];
				}
			}
		} else
			pre[np] = 1;
		last = np;
	}

	int cnt[maxn<<1], sum[maxn<<1], du[maxn<<1];

	int solve () {
		int ret = 0;
		for (int i = 1; i <= sz; i++)
			cnt[i] = sum[i] = du[i] = 0;

		for (int i = 1; i <= sz; i++) {
			for (int j = 0; j < SIGMA_SIZE; j++)
				du[g[i][j]]++;
		}

		queue<int> que;
		que.push(1);
		cnt[1] = 1;

		while (!que.empty()) {
			int u = que.front();
			que.pop();

			ret = (ret + sum[u]) % mod;
		
			for (int i = 0; i < SIGMA_SIZE; i++) {
				int v = g[u][i];

				du[v]--;
				if (du[v] == 0 && v) que.push(v);

				if (v == 0 || (i == 0 && u == 1)) continue;
				if (i == 10) continue;
				cnt[v] = (cnt[u] + cnt[v]) % mod;
				sum[v] = (sum[v] + sum[u] * 10 % mod + cnt[u] * i % mod) % mod;
			}
		}
		return ret;
	}
}SA;

int N;
char str[maxn];

int main () {
	while (scanf("%d", &N) == 1) {
		SA.init();
		while (N--) {
			scanf("%s", str);
			int n = strlen(str);
			for (int i = 0; i < n; i++) SA.insert(str[i] - '0');
			SA.insert(10);
		}
		printf("%d\n", SA.solve());
	}
	return 0;
}
