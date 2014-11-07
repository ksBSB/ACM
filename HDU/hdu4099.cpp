#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;
const int sigma_size = 10;

struct Bign {
	int c, s[maxn];
	Bign() {}

	void operator = (int a) {
		c = 0;
		memset(s, 0, sizeof(s));
		while (a) {
			s[c++] = a % 10;
			a /= 10;
		}
	}

	void put() {
		for (int i = 1; i <= 40 && i <= c; i++)
			printf("%d", s[c-i]);
		printf("\n");
	}
}num[3];

void add(const Bign& a, const Bign& b, Bign& ans) {
	int tmp = 0;

	ans.c = max(a.c, b.c);
	for (int i = max(min(a.c, b.c) - 50, 0); i < a.c || i < b.c; i++) {
		if (i < a.c) tmp += a.s[i];
		if (i < b.c) tmp += b.s[i];
		ans.s[i] = tmp % 10;
		tmp /= 10;
	}

	while (tmp) {
		ans.s[ans.c++] = tmp % 10;
		tmp /= 10;
	}
}

struct Tire {
	int sz, g[maxn * 10][sigma_size];
	int val[maxn * 10];

	void init();
	int find(char* s);
	void insert(const Bign& a, int x);
}T;

void init () {
	num[0] = 1;
	num[1] = 1;

	T.init();
	T.insert(num[0], 1);
	T.insert(num[1], 2);

	int t = 2;
	for (int i = 2; i < 100000; i++) {
		add(num[(t+1)%3], num[(t+2)%3], num[t]);
		T.insert(num[t], i + 1);
		t = (t + 1) % 3;
	}
}

int main () {
	init();
	int cas;
	char s[60];;

	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", s);
		printf("Case #%d: %d\n", kcas, T.find(s) - 1);
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::find(char* s) {
	int n = strlen(s), u = 0;
	for (int i = 0; i < n; i++) {
		int v = s[i] - '0';

		if (g[u][v] == 0)
			return 0;
		u = g[u][v];
	}
	return val[u];
}

void Tire::insert(const Bign& a, int x) {
	int u = 0;
	for (int i = 1; i <= 40 && i <= a.c; i++) {
		int v = a.s[a.c - i];

		if (g[u][v] == 0) {
			val[sz] = x;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
}
