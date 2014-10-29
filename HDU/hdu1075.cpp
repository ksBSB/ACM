#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 5000000;
const int sigma_size = 26;

struct Tire {
	int sz;
	int g[maxn][sigma_size];
	int val[maxn];

	void init ();
	int idx(char ch);
	void insert(char* s, int x);
	int find(char* s);
}S;

char r[500000][15], op[3005], word[15];

void solve (int& p) {
	if (p == 0)
		return;

	word[p++] = '\0';
	int x = S.find(word);
	if (x)
		printf("%s", r[x]);
	else
		printf("%s", word);
	p = 0;
}

int main () {
	while (scanf("%s", op) == 1) {
		S.init();
		int n = 1;

		while (scanf("%s", op), strcmp(op, "END")) {
			strcpy(r[n], op);
			scanf("%s", op);
			S.insert(op, n++);
		}

		scanf("%s", op);
		getchar();
		while (gets(op), strcmp(op, "END")) {
			int len = strlen(op), p = 0;
			for (int i = 0; i < len; i++) {
				if (op[i] >= 'a' && op[i] <= 'z')
					word[p++] = op[i];
				else {
					solve(p);
					printf("%c", op[i]);
				}
			}
			solve(p);
			printf("\n");
		}
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx(char ch) {
	return ch - 'a';
}

int Tire::find(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0)
			return 0;
		u = g[u][v];
	}
	return val[u];
}

void Tire::insert(char* s, int x) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0) {
			val[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}

		u = g[u][v];
	}

	val[u] = x;
}
