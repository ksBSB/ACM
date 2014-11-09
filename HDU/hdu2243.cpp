#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

const int maxn = 50;
const int sigma_size = 26;

struct Mat {
	int r, c;
	ll s[maxn][maxn];
	Mat(int r = 0, int c = 0) { init(r, c);}
	void init(int r, int c) {
		this->r = r;
		this->c = c;
		memset(s, 0, sizeof(s));
	}
	Mat operator * (const Mat& a) {
		Mat ret(r, a.c);
		for (int k = 0; k < c; k++) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < a.c; j++)
					ret.s[i][j] += s[i][k] * a.s[k][j];
		}
		return ret;
	}
};

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	Mat solve();
}A;

int N;
ll L;

void put (Mat x) {
	for (int i = 0; i < x.r; i++) {
		for (int j = 0; j < x.c; j++)
			printf("%llu ", x.s[i][j]);
		printf("\n");
	}
}

ll pow_mat (Mat x, ll n) {

	Mat ret(x.r, 1);
	ret.s[0][0] = ret.s[A.sz+1][0] = 1;

	while (n) {
		if (n&1)
			ret = x * ret;
		x = x * x;
		n >>= 1;
	}
	int p = ret.r;
	return ret.s[p-1][0] - ret.s[p-3][0];
}

int main () {
	//while (scanf("%d%llu", &N, &L) == 2) {
	while (cin >> N >> L) {
		A.init();
		char w[20];
		for (int i = 1; i <= N; i++) {
			cin >> w;
			A.insert(w, i);
		}
		Mat X = A.solve();
		//printf("%llu\n", pow_mat(X, L + 1));
		cout << pow_mat(X, L + 1) << endl;
	}
	return 0;
}

Mat Aho_Corasick::solve() {
	getFail();
	Mat ret(sz + 3, sz + 3);

	for (int i = 0; i < sz; i++) {
		if (tag[i] || last[i])
			continue;

		for (int v = 0; v < sigma_size; v++) {
			int u = i;
			while (u && g[u][v] == 0)
				u = fail[u];

			u = g[u][v];
			ret.s[u][i]++;
		}
		ret.s[sz][i]++;
	}
	ret.s[sz][sz] = 1;
	ret.s[sz+1][sz+1] = 26;
	ret.s[sz+2][sz+1] = ret.s[sz+2][sz+2] = 1;
	return ret;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'a';
}

void Aho_Corasick::put(int x, int y) {
}

void Aho_Corasick::insert(char* str, int k) {
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
	tag[u] = k;
}

void Aho_Corasick::match(char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

		if (tag[u])
			put(i, u);
		else if (last[u])
			put(i, last[u]);
	}
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
