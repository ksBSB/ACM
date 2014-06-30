#include <stdio.h>
#include <string.h>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 20;
const int M = 50;

int ans, g[N];
set<string> rec;

int d[M], c[M];
char sta[M][N];

void handle() {
	for (int i = 0; i < 32; i++) {
		int k = i, t = 0;
		for (int j = 0; j < 5; j++) {
			int m = k % 2; k /= 2;
			t = t * 2 + m;
			sta[i][4-j] = '0' + m;
		}
		d[i] = t;
	}
}

void rechange(int id, char* str) {
	int t = 0, k = 0;
	for (int i = 0; i < 5; i++) {
		t = t * 2 + str[i] - '0';
		k = k * 2 + str[4-i] - '0';
	}
	c[t]++; c[k]++;
}

bool init() {
	rec.clear();
	ans = 0;
	memset(c, 0, sizeof(c));

	char str[N];
	for (int i = 0; i < 10; i++) {
		scanf("%s", str);
		if (strcmp(str, "END") == 0) return false;
		rechange(i, str); 
	}
	return true;
}

void add(char (*x)[N], char (*y)[N]) {
	string str;
	for (int i = 0; i < 5; i++) str = str + x[i];
	for (int i = 0; i < 5; i++) str = str + y[i];
	rec.insert(str);
}

void ret(char(*x)[N]) {
	char y[N][N];
	for (int i = 0; i < 5; i++) strcpy(y[i], x[i]);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) x[j][4-i] = y[i][j];
	}
}

void del() {
	ans++;
	char x[N][N], y[N][N];
	for (int i = 0; i < 5; i++) {
		strcpy(x[i], sta[g[i]]);
		strcpy(y[i], sta[g[i+5]]);
	}
	for (int i = 0; i < 4; i++) {
		add(x, y);
		ret(x); ret(y);
	}

	for (int i = 0; i < 5; i++) {
		strcpy(x[i], sta[g[4-i]]);
		strcpy(y[i], sta[d[g[i+5]]]);
	}
	for (int i = 0; i < 4; i++) {
		add(x, y);
		ret(x); ret(y);
	}
}

bool judge() {
	int r[M];
	memset(r, 0, sizeof(r));

	for (int i = 0; i < 5; i++) {
		int k = 0;
		for (int j = 0; j < 5; j++) {
			k = k * 2 + ( g[j] & (1<<i) ? 0 : 1 );
		}

		if (r[k] >= c[k]) return false;
		g[i+5] = k;
		r[k]++; r[d[k]]++;
	}

	string str;
	for (int i = 0; i < 10; i++) {
		str = str + sta[g[i]];
	}

	if (rec.find(str) != rec.end()) return false;
	return true;
}

void dfs(int deep) {
	if (deep >= 5) {
		if (judge()) del();
		return;
	}

	for (int i = 0; i < 32; i++) {
		if (c[i] == 0) continue;
		c[i]--; c[d[i]]--;
		g[deep] = i; 
		dfs(deep + 1);

		c[i]++; c[d[i]]++;
	}
}

int main() {
	handle();
	while (init()) {
		dfs(0);
		printf("%d\n", ans / 2);
	}
	return 0;
}
