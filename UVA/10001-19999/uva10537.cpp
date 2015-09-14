#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 55;
const int inf = 0x3f3f3f3f;

int IDX(char ch) { if (ch >= 'A' && ch <= 'Z') return ch - 'A'; else return 26 + ch - 'a'; }
char RIDX(int x) { if (x < 26) return 'A' + x; else return 'a' + x - 26; }

int N = 52, M, S, E, L, V[maxn];
ll D[maxn];
vector<int> G[maxn], ans;

struct State {
	int u;
	ll d;
	State (int u = 0, ll d = 0): u(u), d(d) {}
	bool operator < (const State& u) const { return d > u.d; }
};

void init () {
	for (int i = 0; i <= N; i++) G[i].clear();

	char s[5], e[5];
	for (int i = 0; i < M; i++) {
		scanf("%s%s", s, e);
		int u = IDX(s[0]), v = IDX(e[0]);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%d%s%s", &L, s, e);
	S = IDX(s[0]), E = IDX(e[0]);
}

ll limit (int x, ll w) {
	if (x >= 26) return w+1;
	ll l = 0, r = inf;
	while (l < r) {
		ll mid = (l + r) >> 1;
		ll t = mid + w;
		if (t - (t + 19) / 20 >= w) r = mid;
		else l = mid + 1;
	}
	return w + l;
}

ll consume(int u, ll d) {
	if (u >= 26) return 1;
	else return (d + 19) / 20;
}

void put (int u) {
	ans.push_back(u);
	if (u == E) return;

	int rec = -1;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (D[u] - consume(v, D[u]) == D[v] && (rec == -1 || rec > v))
			rec = v;
	}
	put(rec);
}

void dijkstra () {
	memset(V, 0, sizeof(V));
	memset(D, inf, sizeof(D));

	D[E] = L;

	priority_queue<State> Q;
	Q.push(State(E, D[E]));

	while (!Q.empty()) {
		int u = Q.top().u;
		Q.pop();

		if (V[u]) continue;
		V[u] = 1;
		ll w = limit(u, D[u]);

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (D[v] > w) {
				D[v] = w;
				Q.push(State(v, w));
			}
		}
	}

	printf("%lld\n", D[S]);
	ans.clear();
	put(S);
	for (int i = 0; i < ans.size(); i++) {
		printf("%c%c", RIDX(ans[i]), i == ans.size()-1 ? '\n' : '-');
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &M) == 1 && M != -1) {
		init ();
		printf("Case %d:\n", cas++);
		dijkstra();
	}
	return 0;
}
