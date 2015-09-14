#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int maxm = 25;

int N, jump[maxn];
bool flag, vis[maxn][maxm];
vector<string> vstr;
vector<int> G[maxn][maxm];

void init () {
	vstr.clear();
	flag = true;
	memset(vis, false, sizeof(vis));

	char name[maxm], code[maxm];
	for (int i = 1; i <= N; i++) {
		scanf("%s%s", name, code);
		vstr.push_back(code);
	}

	for (int i = 0; i < vstr.size(); i++) {
		for (int j = 0; j < vstr[i].size(); j++)
			G[i][j] .clear();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <	N; j++) {
			int szj = vstr[j].size(), szi = vstr[i].size();
			int p = jump[0] = 0;
			string t = vstr[j] + "#" + vstr[i];

			for (int k = 1; k < t.size(); k++) {
				while (p > 0 && t[k] != t[p]) p = jump[p-1];
				if (t[k] == t[p]) p++;
				jump[k] = p;
				if (p == szj && i != j) {
					int ind = k - szj * 2;
					G[i][ind].push_back(j);
				}
			}

			int u = jump[t.size()-1];
			while (u > 0) {
				int ind = szi - u;
				if (i != j || ind)
					G[i][ind].push_back(j);
				u = jump[u-1];
			}
		}
	}
}

bool dfs (int u, int p) {
	if (p == vstr[u].size()) return true;

	if (vis[u][p]) return false;
	vis[u][p] = true;

	bool ret = false;
	for (int i = 0; i < G[u][p].size() && !ret; i++) {
		int v = G[u][p][i];
		int nxt = p + vstr[v].size();
		if (nxt <= vstr[u].size())
			ret |= dfs(u, nxt);
		else
			ret |= dfs(v, vstr[u].size()-p);
	}
	return ret;
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init ();
		for (int i = 0; i < N && flag; i++)
			flag ^= dfs(i, 0);
		printf("Case #%d: %s\n", cas++, flag ? "Not ambiguous." : "Ambiguous.");
	}
	return 0;
}
