#include <stdio.h>
#include <string.h>
#include <string>
#include <set>
#include <stack>
#include <iostream>

using namespace std;

const char sign[4] = { '*', '+', '-' };
const int N = 20;

int n, c[N];
bool flag;
char str[N];
set<string> s;

void init() {
	s.clear();
	n = strlen(str) - 2;
	flag = true;
}

bool judge(char* t) {
	int len = strlen(t);
	int num[N], cNum = 0, cOp = 0;
	char op[N];


	int sum = 0;
	bool bo = false, ok = false;
	for (int i = 0; i <= len; i++) {
		if (t[i] >= '0' && t[i] <= '9') {
			sum = sum * 10 + t[i] - '0';

			if (bo) return false;
			if (sum == 0) bo = true;

		} else if(ok) {
			int u = num[--cNum];
			num[cNum++] = sum * u; sum = 0; bo = false;

			if (t[i] != '*' && t[i] != '\0') {
				op[cOp++] = t[i]; ok = false;
			}

		} else if (t[i] == '*') {

			num[cNum++] = sum; sum = 0; ok = true; bo = false;
		} else {

			num[cNum++] = sum; sum = 0;
			if (t[i] != '\0') op[cOp++] = t[i];
			bo = false;
		}
	}

	sum = num[0];
	for (int i = 1; i < cNum; i++) {
		if (op[i - 1] == '-') sum -= num[i];
		else sum += num[i];
	}

	if (sum == 2000) return true;
	return false;
}

void handle() {
	char f[N];
	int t = 0;
	for (int i = 0; i <= n; i++) {
		f[t++] = str[i];
		if(i != n && c[i] != 3) f[t++] = sign[c[i]];
	}	
	f[t] = '\0';

	if (judge(f)) {
		string g = f;
		s.insert(g);
		flag = false;
	}
}

void dfs(int d) {
	if (d >= n) {
		handle(); return;
	}

	for (c[d] = 0; c[d] < 4; c[d]++) dfs(d + 1);
}

void solve() {
	if (strcmp(str, "2000=") == 0) {
		printf("  IMPOSSIBLE\n");
		return;
	}
	dfs(0);

	if (flag) printf("  IMPOSSIBLE\n");
	else {
		for (set<string>::iterator i = s.begin(); i != s.end(); i++)
			cout << "  " << *i << "=" << endl;
	}
}

int main () {
	int cas = 1;
	while (scanf("%s", str) == 1 && strcmp(str, "=") ) {
		printf("Problem %d\n", cas++);
		init();
		solve();
	}
	return 0;
}
