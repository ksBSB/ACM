#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int N = 150;

struct Tree {
	int cnt;
	char node[N];
	vector<int> g[N];
	void clear() {
		cnt = 0;
		memset(node, 0, sizeof(node));
		for (int i = 0; i < N; i++) g[i].clear();
	}
};

int read(Tree& T, int far) {
	int x = T.cnt++;
	if (far >= 0) T.g[x].push_back(far);

	char ch;
	scanf(" %c %c", &T.node[x], &ch);

	if (ch != '(') {
		ungetc(ch, stdin);
		return x;
	}

	while (true) {
		T.g[x].push_back(read(T, x));
		if (scanf(" %c", &ch) != 1 || ch != ',') break;
	}
	return x;
}

void readTree(Tree& T) {
	T.clear();
	read(T, -1);
}

map<vector<int>, int> rec;

int solve (const Tree& t, int x, int far = -1) {
	vector<int> v;

	if (far < 0) {
		for (int i = 0; i < t.g[x].size(); i++) {
			int u = t.g[x][i];
			v.push_back(solve(t, u, x));
		}

		int p = 0, n = v.size();
		for (int s = 1; s < n; s++) {
			for (int i = p, j = s, k = 0; k < n; k++) {
				if (v[i] != v[j]) {
					if (v[j] < v[i]) p = s;
					break;
				}

				if (++i >= n) i = 0;
				if (++j >= n) j = 0;
			}
		}
		rotate(v.begin(), v.begin() + p, v.end());

	} else {

		int i;
		for (i = 0; t.g[x][i] != far; i++);
		
		while (true) {
			if (++i >= t.g[x].size()) i = 0;
			int u = t.g[x][i];
			if (u == far) break;
			v.push_back(solve(t, u, x));
		}
	}
	v.push_back(t.node[x]);

	int key;
	if (rec.count(v) > 0) {
		key = rec[v];
	} else {
		key = rec.size();
		rec[v] = key;
	}
	return key;
}

bool judge(const Tree& T1, const Tree& T2) {
	if (T1.cnt != T2.cnt) return false;

	rec.clear();
	for (int i = 0; i < T1.cnt; i++) {
		if (solve(T1, i, -1) == solve(T2, 0, -1)) return true;
	}
	return false;
}

int main () {
	int cas;
	Tree T1, T2;
	scanf("%d", &cas);
	while (cas--) {
		readTree(T1);
		readTree(T2);
		printf("%s\n", judge(T1, T2) ? "same" : "different");
	}
	return 0;
}
