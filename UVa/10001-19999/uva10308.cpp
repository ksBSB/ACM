#include <stdio.h>
#include <string.h>
#include <vector>
#define max(a,b) (a)>(b)?(a):(b)
using namespace std;
const int N = 10005;
const int INF = (1 << 31) - 1;

struct State {
	int id;
	int val;
	State (int x = 0, int c = 0) {
		id = x, val = c;
	}	
};

vector<State> v[N];
int ans, rec[N];

void init() {
	ans = 0;
	for (int i = 0; i < N; i++)
		v[i].clear();
	memset(rec, 0, sizeof(rec));
}

void add(int x, int y, int value) {
	State c(y, value);
	v[x].push_back(c);
}

int dfs(int x) {
	int Max = 0;
	int n = v[x].size();

	rec[x] = 1;
	for (int i = 0; i < n; i++) {
		if (rec[v[x][i].id]) continue;
		int c = dfs(v[x][i].id) + v[x][i].val;

		ans = max(Max + c, ans);
		Max = max(Max, c);
	}
	rec[x] = 0;
	return Max;
}

int main () {
	int a, b, value;
	char str[100];
	while (gets(str)) {
		init();
		while (str[0] != '\0') {
			sscanf(str, "%d%d%d", &a, &b, &value);
			add(a, b, value);
			add(b, a, value);
			if (!gets(str)) break;
		}

		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
