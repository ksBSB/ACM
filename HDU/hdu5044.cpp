#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;

inline void scanf_(int &num) {  
	char in;  
	bool neg=false;  
	while(((in=getchar()) > '9' || in<'0') && in!='-') ;  
	if(in=='-') {  
		neg = true;  
		while((in=getchar()) >'9' || in<'0');  
	}  
	num=in-'0';  
	while(in=getchar(),in>='0'&&in<='9')  
		num*=10,num+=in-'0';  
	if(neg)  
		num=0-num;  
} 

ll c[2][maxn];
int N, M, E, first[maxn], jump[maxn * 2];
int id, idx[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn], dep[maxn];

struct Edge {
	int u, v;
}ed[maxn * 2];

inline void add_Edge(int u, int v) {
	ed[E].u = u, ed[E].v = v;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int d) {
	dep[u] = d;
	far[u] = pre;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == pre)
			continue;
		dfs(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs (int u, int rot) {
	top[u] = rot;
	idx[u] = ++id;

	if (son[u])
		dfs(son[u], rot);
	for (int i = first[u] ; i + 1; i = jump[i]) {
		int v = ed[i].v;
		if (v == far[u] || v == son[u])
			continue;
		dfs(v, v);
	}
}

void init () {
	int u, v;
	E = id = 0;
	memset(c, 0, sizeof(c));
	memset(first, -1, sizeof(first));
	//scanf("%d%d", &N, &M);
	scanf_(N), scanf_(M);
	for (int i = 1; i < N; i++) {
		//scanf("%d%d", &u, &v);
		scanf_(u), scanf_(v);
		add_Edge(u, v);
		add_Edge(v, u);
	}
	dfs(1, 0, 0);
	dfs(1, 1);
}

inline void insert (int k, int l, int r, int w) {
	c[k][l] += w;
	c[k][r+1] -= w;
}

void modify(int k, int u, int v, int w) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		insert(k, idx[p], idx[u], w);
		u = far[p];
		p = top[u];
	}

	if (dep[u] > dep[v])
		swap(u, v);
	if (k) {
		if (u == v) return;
		insert(k, idx[son[u]], idx[v], w);
	} else
		insert(k, idx[u], idx[v], w);
}

int main () {
	int cas;
	scanf_(cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int u, v, w;
		char op[10];
		while (M--) {
			scanf("%s", op);
			scanf_(u), scanf_(v), scanf_(w);
			//scanf("%s%d%d%d", op, &u, &v, &w);
			modify(op[3]-'1', u, v, w);
		}

		for (int i = 0; i < 2; i++) {
			ll mv = 0;
			for (int j = 1; j <= N; j++) {
				mv += c[i][j];
				c[i][j] = mv;
			}
		}

		printf("Case #%d:\n", kcas);
		for (int i = 1; i <= N; i++)
			printf("%I64d%c", c[0][idx[i]], i == N ? '\n' : ' ');

		for (int i = 0; i < N - 1; i++) {
			int t = i * 2;
			u = dep[ed[t].u] < dep[ed[t].v] ? ed[t].v : ed[t].u;
			printf("%I64d%c", c[1][idx[u]], i == N - 2 ? '\n' : ' ');
		}
		if (N == 1)
			printf("\n");
	}
	return 0;
}
