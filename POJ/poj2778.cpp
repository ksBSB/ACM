#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int sigma_size = 4;
const int mod = 100000;
typedef long long ll;

struct Mat {
	int r, c;
	ll s[maxn][maxn];
	Mat (int r = 0, int c = 0) {
		init(r, c);
	}
	void init (int r, int c) {
		this->r = r;
		this->c = c;
		memset(s, 0, sizeof(s));
	}
	friend Mat operator * (const Mat& a, const Mat& b);
}tmp;

Mat operator * (const Mat& a, const Mat& b) {
	tmp.init(a.r, b.c);
	for (int k = 0; k < a.c; k++) {
		for (int i = 0; i < a.r; i++)
			for (int j = 0; j < b.c; j++)
				tmp.s[i][j] = (tmp.s[i][j] + a.s[i][k] * b.s[k][j]) % mod;
	}
	return tmp;
}

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

int M, N;
char w[15];

int pow_mat(Mat x, int n) {

	Mat ans(x.r, 1);
	ans.s[0][0] = 1;

	while (n) {
		if (n&1)
			ans = x * ans;
		x = x * x;
		n >>= 1;
	}
	int ret = 0;
	for (int i = 0; i < A.sz; i++) {
		if (A.tag[i] || A.last[i])
			continue;
		ret = (ret + ans.s[i][0]) % mod;
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &M, &N) == 2) {
		A.init();
		for (int i = 1; i <= M; i++) {
			scanf("%s", w);
			A.insert(w, i);
		}
		Mat u = A.solve();
		printf("%d\n", pow_mat(u, N));
	}
	return 0;
}

Mat Aho_Corasick::solve() {
	getFail();
	Mat u(sz, sz);

	for (int i = 0; i < sz; i++) {
		if (tag[i] || last[i])
			continue;

		for (int j = 0; j < 4; j++) {
			int t = i;
			while (t && g[t][j] == 0)
				t = fail[t];

			t = g[t][j];
			u.s[t][i]++;
		}
	}
	return u;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	switch (ch) {
		case 'A':
			return 0;
		case 'C':
			return 1;
		case 'G':
			return 2;
		case 'T':
			return 3;
	}
	return 4;
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
