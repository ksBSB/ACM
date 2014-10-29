#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5+5;
const int maxm = 15;
const int sigma_size = 2;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s);
	int find(char* s);
}S;

int N;
char s[maxn][maxm], op[maxm];

bool input () {
	N = 0;
	S.init();

	while (scanf("%s", op) == 1 && strcmp(op, "9")) {
		S.insert(op);
		strcpy(s[N++], op);
	}
	return N;
}

bool judge() {
	for (int i = 0; i < N; i++) {
		if (S.find(s[i]))
			return false;
	}
	return true;
}

int main () {
	int cas = 1;
	while (input()) {
		printf("Set %d is %s\n", cas++, judge() ? "immediately decodable" : "not immediately decodable");
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
	return ch - '0';
}

int Tire::find(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (val[u])
			return 1;
		u = g[u][v];
	}
	return val[u] - 1;
}

void Tire::insert(char* s) {
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
	val[u] = 1;
}
