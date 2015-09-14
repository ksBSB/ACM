#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int sigma_size = 26;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

    void init();
    int idx(char ch);
    void insert(char* str);
    void getFail();
    ll match(string str);
    ll put(int x);
}AC;

int N, M;
string s[maxn];
char str[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++) {
			scanf("%s", str);
			s[i] = str;
		}

		AC.init();
		for (int i = 1; i <= M; i++) {
			scanf("%s", str);
			AC.insert(str);
		}
		AC.getFail();
		for (int i = 1; i <= N; i++)
			printf("%lld\n", AC.match(s[i]));
	}
    return 0;
}

void Aho_Corasick::init() {
    sz = 1;
    tag[0] = 0;
    memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
    return ch - 'a';
}

ll Aho_Corasick::put(int x) {
	ll ret = tag[x];
	while (last[x]) {
		x = last[x];
		ret += tag[x];
	}
	return ret;
}

void Aho_Corasick::insert(char* str) {
    int u = 0, n = strlen(str);

    for (int i = 0; i < n; i++) {
        int v = idx(str[i]);
        if (g[u][v] == 0) {
            tag[sz] = 0;
            memset(g[sz], 0, sizeof(g[sz]));
            g[u][v] = sz++;
        }
        u = g[u][v];
    }
    tag[u]++;
}

ll Aho_Corasick::match(string str) {
    int n = str.length(), u = 0;
	ll ret = 0;
    for (int i = 0; i < n; i++) {
        int v = idx(str[i]);
        while (u && g[u][v] == 0)
            u = fail[u];

        u = g[u][v];

        if (tag[u])
            ret += put(u);
        else if (last[u])
            ret += put(last[u]);
    }
	return ret;
}

void Aho_Corasick::getFail() {
    queue<int> que;

    for (int i  = 0; i < sigma_size; i++) {
        int u = g[0][i];
        if (u) {
            fail[u] = last[u] = 0;
            que.push(u);
        }
    }

    while (!que.empty()) {
        int r = que.front();
        que.pop();

        for (int i = 0; i < sigma_size; i++) {
            int u = g[r][i];

            if (u == 0) {
                g[r][i] = g[fail[r]][i];
                continue;
            }

            que.push(u);
            int v = fail[r];
            while (v && g[v][i] == 0)
                v = fail[v];

            fail[u] = g[v][i];
            last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
        }
    }
}
