#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>

using namespace std;
map<string, string> v;
string s, e;

inline char cat (char a, char b) {
	if (a == 'a') {
		if (b == 'c') return 'a';
		return 'b';
	} else if (a == 'b') {
		return 'c' - b + 'a';
	} else {
		if (b == 'a') return 'a';
		return 'c';
	}
}

bool dfs(string c) {

	int len = c.length();

	if (len == 1)
		return c == e;

	for (int i = 1; i < len; i++) {
		string tmp = "";
		for (int j = 0; j < i-1; j++)
			tmp = tmp + c[j];
		tmp = tmp + cat(c[i-1], c[i]);
		for (int j = i + 1; j < len; j++)
			tmp = tmp + c[j];

		if (v.count(tmp))
			continue;

		v[tmp] = c;
		if (dfs(tmp))
			return true;
	}
	return false;
}

void put(string c) {
	if (c != s)
		put(v[c]);
	cout << c << endl;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		cin >> s >> e;

		v.clear();

		if (dfs(s))
			put(e);
		else
			printf("None exist!\n");

		if (cas)
			printf("\n");
	}
	return 0;
}
