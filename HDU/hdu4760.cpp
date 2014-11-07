#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, ll> pii;
typedef set<pii>::iterator iter;
const int maxn = 1024 * 15 + 10;
const int maxm = 105;
const int sigma_size = 2;

struct Tire {
	int sz, sv;
	int g[maxn * maxm][sigma_size];
	int idx[maxn * maxm], cnt[1030];
	set<pii> ans, vis[maxn];

	void init();
	int newSet();
	void addSet(int id, ll limt);
	void insert(char* str, pii x);
	void remove(char* str, pii x);
	void find(char* str);
	bool judge(char* a, char* b);
}T;

struct Network {
	int n;
	ll suf[20];
	char ip[20][maxm];
	Network() { 
		n = 0; 
		memset(suf, 0, sizeof(suf));
	}
}net[1030];

ll change(char* ans, bool flag) {
	char str[105];
	int n = strlen(str), a[4], b;

	if (flag)
		scanf("%d.%d.%d.%d/%d", &a[0], &a[1], &a[2], &a[3], &b);
    else {
		scanf("%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
		b = 32;
	}

	int t = 0;
	ll ret = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 7; j >= 0; j--) {
			if (t < b)
				ans[t] = ((a[i]>>j)&1) + '0';
			else if (((a[i]>>j)&1))
				ret |= (1LL<<(31-t));
			t++;
		}
	}
	ans[t] = '\0';
	return ret;
}

int main () {
	int id;
	char op[5], a[maxm], b[maxm], c[maxm];

	T.init();
	while (scanf("%s", op) == 1) {
		if (op[0] == 'E') {
			scanf("%d", &id);
			scanf("%d", &net[id].n);

			for (int i = 0; i < net[id].n; i++) {
				net[id].suf[i] = change(net[id].ip[i], a);
				T.insert(net[id].ip[i], make_pair(id, net[id].suf[i]));
			}

		} else if (op[0] == 'D') {
			scanf("%d", &id);

			for (int i = 0; i < net[id].n; i++)
				T.remove(net[id].ip[i], make_pair(id, net[id].suf[i]));
			net[id].n = 0;

		} else {
			change(a, 0);
			change(b, 0);
			printf("%c\n", T.judge(a, b) ? 'F' : 'D');
		}
	}
	return 0;
}

bool Tire::judge(char* a, char* b) {
	memset(cnt, 0, sizeof(cnt));

	T.find(a);
	for (iter i = ans.begin(); i != ans.end(); i++)
		cnt[i->first] = 1;

	T.find(b);
	for (iter i = ans.begin(); i != ans.end(); i++)
		if (cnt[i->first])
			return true;
	return false;
}

void Tire::init() {
	sz = sv = 1;
	idx[0] = 0;
	vis[0].clear();
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::newSet() {
	vis[sv].clear();
	return sv++;
}

void Tire::addSet(int id, ll limt) {
	for (iter i = vis[id].begin(); i != vis[id].end(); i++)
		if (i->second <= limt)
			ans.insert(*i);
}

void Tire::insert(char* str, pii x) {
	int u = 0, n = strlen(str);
	for (int i = 0; i < n; i++) {
		int v = str[i] - '0';
		if (g[u][v] == 0) {
			idx[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	if (idx[u] == 0)
		idx[u] = newSet();
	vis[idx[u]].insert(x);
}

void Tire::remove(char* str, pii x) {
	int u = 0, n = strlen(str);
	for (int i = 0; i < n; i++) {
		int v = str[i] - '0';
		if (g[u][v] == 0) {
			idx[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	vis[idx[u]].erase(x);
}

void Tire::find(char* str) {
	ans.clear();

	ll ret = 0;
	int u = 0, n = strlen(str);

	for (int i = 0; i < n; i++) {
		int v = str[i] - '0';

		if (g[u][v] == 0)
			return;

		u = g[u][v];
		if (idx[u]) {
			ll ret = 0;
			for (int j = i+1; j < n; j++)
				if (str[j] == '1')
					ret |= (1LL<<(31-j));
			addSet(idx[u], ret);
		}
	}
}
