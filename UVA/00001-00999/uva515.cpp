#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int N = 105;
const int INF = 0x3f3f3f3f;

int n, m, tmp;
vector< pair<int, int> > v[N];

void init() {
	scanf("%d", &m);
	tmp = n + 1;

	v[tmp].clear();
	for (int i = 0; i < tmp; i++)
		v[i].clear(), v[tmp].push_back( make_pair(i, 0) );

	int s, t, k;
	char ch[N];

	for (int i = 0; i < m; i++) {
		scanf("%d%d%s%d", &s, &t, ch, &k);
		if (strcmp(ch, "gt") == 0) {
			v[s + t].push_back( make_pair(s - 1, -k -1) );
		} else {
			v[s - 1].push_back( make_pair(s + t, k -1) );
		}
	}
}

bool spfa() {
	int u, w, s, t;
	int vis[N], d[N], c[N];
	queue<int> q;
	memset(vis, 0, sizeof(vis));
	memset(c, 0, sizeof(c));
	memset(d, INF, sizeof(d));

	d[tmp] = 0; vis[tmp] = 1, c[tmp] = 1;
	q.push(tmp);

	while ( !q.empty() ) {
		u = q.front(); q.pop();
		vis[u] = 0;

		t = v[u].size();
		for (int i = 0; i < t; i++) {
			s = v[u][i].first, w = v[u][i].second;

			if (d[s] > d[u] + w) {
				d[s] = d[u] + w;
				c[s]++;

				if (c[s] > tmp + 1) return false;

				if ( !vis[s] ) {
					q.push(s);
					vis[s] = 1;
				}
			}
		}
	}

	return true;
}

int main () {

	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("%s\n", spfa() ? "lamentable kingdom" : "successful conspiracy");
	}
	return 0;
}
