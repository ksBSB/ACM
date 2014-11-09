#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 505;
const int sigma_size = 256;
const int bw = 128;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
}A;

struct bign {
	int len, num[100];

	bign () {
		len = 0;
		memset(num, 0, sizeof(num));
	}
	bign (int number) {*this = number;}
	bign (const char* number) {*this = number;}

	void delzero ();
	void Put ();

	void operator = (int number);
	void operator = (char* number);

	bool operator <  (const bign& b) const;
	bool operator >  (const bign& b) const { return b < *this; }
	bool operator <= (const bign& b) const { return !(b < *this); }
	bool operator >= (const bign& b) const { return !(*this < b); }
	bool operator != (const bign& b) const { return b < *this || *this < b;}
	bool operator == (const bign& b) const { return !(b != *this); }

	void operator ++ ();
	void operator -- ();
	bign operator + (const int& b);
	bign operator + (const bign& b);
	bign operator - (const int& b);
	bign operator - (const bign& b);
	bign operator * (const int& b);
	bign operator * (const bign& b);
	bign operator / (const int& b);
	int operator % (const int& b);
}dp[2][maxn];

int N, M, K, tab[55];
char s[55];

void solve() {
	int n = A.sz;
	for (int i = 0; i < n; i++)
		dp[0][i] = 0;
	dp[0][0] = 1;

	for (int i = 0; i < M; i++) {
		int now = i&1, nxt = !(i&1);
		for (int i = 0; i < n; i++) dp[nxt][i] = 0;

		for (int i = 0; i < n; i++) {
			if (A.tag[i] || A.last[i])
				continue;

			for (int j = 0; j < N; j++) {
				int v = tab[j], u = i;
				while (u && A.g[u][v] == 0)
					u = A.fail[u];
				u = A.g[u][v];
				dp[nxt][u] = dp[nxt][u] + dp[now][i];
			}
		}
	}

	int now = (M&1);
	bign ans = 0;
	for (int i = 0; i < n; i++) {
		if (A.tag[i] || A.last[i])
			continue;
		ans = ans + dp[now][i];
	}
	ans.Put();
	printf("\n");
}

int main () {
	while (scanf("%d%d%d%*c", &N, &M, &K) == 3) {
		A.init();
		gets(s);
		for (int i = 0; i < N; i++)
			tab[i] = s[i] + bw;

		for (int i = 1; i <= K; i++) {
			gets(s);
			A.insert(s, i);
		}
		A.getFail();
		solve();
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch + bw;
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

void bign::delzero () {
	while (len && num[len-1] == 0)
		len--;

	if (len == 0) {
		num[len++] = 0;
	}
}

void bign::Put () {
	for (int i = len-1; i >= 0; i--) 
		printf("%d", num[i]);
}

void bign::operator = (char* number) {
	len = strlen (number);
	for (int i = 0; i < len; i++)
		num[i] = number[len-i-1] - '0';

	delzero ();
}

void bign::operator = (int number) {

	len = 0;
	while (number) {
		num[len++] = number%10;
		number /= 10;
	}

	delzero ();
}

bign bign::operator + (const int& b) {
	bign a = b;
	return *this + a;
}

bign bign::operator + (const bign& b) {
	int bignSum = 0;
	bign ans;

	for (int i = 0; i < len || i < b.len; i++) {
		if (i < len) bignSum += num[i];
		if (i < b.len) bignSum += b.num[i];

		ans.num[ans.len++] = bignSum % 10;
		bignSum /= 10;
	}

	while (bignSum) {
		ans.num[ans.len++] = bignSum % 10;
		bignSum /= 10;
	}

	return ans;
}
