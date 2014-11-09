#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 512 * 100;
const int sigma_size = 256;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];
	bool vis[520];
	int jump[520];

    void init();
    int idx(char ch);
	void insert(int* str, int k);
	void getFail();
	int match(int* str);
	void put(int u);
}A;

inline int change(char ch) {
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A';
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;
	if (ch == '+')
		return 62;
	return 63;
}

const int maxl = 5005;

char w[maxl];
int s[maxl * 2];

void input(int* s) {

	scanf("%s", w);
	s[0]=0;  
	int n = strlen(w);
	while (n && w[n-1] == '=') n--;
	w[n] = 0;
	for(int i=0,len=0,x=0;w[i];++i){  
		len+=6,x=(x<<6)|change(w[i]);  
		if(len>=8){  
			s[++s[0]]=(x>>(len-8))&0xff;
			len-=8;   
		}  
	} 

	/*
	   for(int i = 1; i <= s[0]; i++)
	   printf(" %d", s[i]);
	   printf("\n");
	   */
}

int N, M;

int main () {
	while (scanf("%d", &N) == 1) {
		A.init();

		for (int i = 1; i <= N; i++) {
			input(s);
			A.insert(s, i);
		}
		A.getFail();

		scanf("%d", &M);
		for (int i = 1; i <= M; i++) {
			input(s);
			printf("%d\n", A.match(s));
		}
		printf("\n");
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch;
}

void Aho_Corasick::put(int u) {
	int p = tag[u];
	while (p && vis[p] == 0) {
		vis[p] = 1;
		p = jump[p];
	}
	if (last[u])
		put(last[u]);
}

void Aho_Corasick::insert(int* str, int k) {
	int u = 0;

	for (int i = 1; i <= str[0]; i++) {
		int v = str[i];
		while (v >= sigma_size);
		if (g[u][v] == 0) {
			tag[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}

	jump[k] = tag[u];
	tag[u] = k;
}

int Aho_Corasick::match(int* str) {
	memset(vis, 0, sizeof(vis));
	int u = 0;

	for (int i = 1; i <= str[0]; i++) {
		int v = str[i];
		while (v >= sigma_size);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

		if (tag[u])
			put(u);
		else if (last[u])
			put(last[u]);
	}

	int ret = 0;
	for (int i = 1; i <= N; i++)
		if (vis[i])
			ret++;
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
