#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 505;

int N, M, P, L, idx[maxn], ridx[maxn];
string str, word, a, b;
map<string, int> Type, Variate;
vector<string> Name;
int G[maxn][maxn];
bool flag;

bool ischar(char ch) { return ch >= 'a' && ch <= 'z'; }
bool match (char ch) { if (str[P] == ch) { P++; return true; } return false; }

int getTypeId (string& s) {
	if (!Type.count(s)) {
		Name.push_back(s);
		int k = Name.size();
		Type[s] = k;
	}
	return Type[s];
}

void getword () {
	word = "";
	while (ischar(str[P])) word += str[P++];
}

bool init () {
	cin >> N;
	Name.clear();
	Type.clear();
	Variate.clear();

	memset(idx, 0, sizeof(idx));
	memset(ridx, 0, sizeof(ridx));
	memset(G, 0, sizeof(G));

	bool flag = true;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		if (Variate.count(a)) flag = false;
		Variate[a] = getTypeId(b);
	}

	cin >> M;
	for (int i = 1; i <= M; i++) {
		cin >> a;
		int u = getTypeId(a), k, x;
		if (ridx[u]) flag = false;
		idx[i] = u, ridx[u] = i;
		G[i][i] = i;

		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> x;
			G[i][x] = x;
		}
	}

	cin >> str;
	P = 0;
	L = str.length();
	return flag;
}

int solve ();

int change () {
	if (!match('(')) return 0;
	int ret = solve();
	if (ret == 0) return ret;
	if (!match(')')) return 0;
	return ret;
}

int getItem () {
	int ret = 0;
	getword();
	if (word.length() == 0) {
		/*
		if (match('(')) {
			ret = solve();
			if (!match(')')) ret = 0;
		}
		*/
		ret = 0;
	} else if (Type.count(word)) {
		ret = ridx[Type[word]];
		int tmp = change();
		ret = G[tmp][ret];
	} else if (Variate.count(word))
		ret = ridx[Variate[word]];
	return ret;
}

int solve () {
	int ret = getItem();

	while (P < L && ret && str[P] == '*') {
		match('*');
		int tmp = getItem();
		ret = G[tmp][ret];
	}
	return ret;
}

bool judge () {
	for (map<string,int>::iterator it = Variate.begin(); it != Variate.end(); it++) {
		if (ridx[it->second] == 0) return false;
		if (Type.count(it->first)) return false;
	}
	return true;
}

int main () {
	int cas;
	cin >> cas;
	while (cas--) {
		bool flag = init();
		if (flag && judge()) {
			int ans = solve();
			if (L != P) ans = 0;
			if (ans) cout << Name[idx[ans]-1] << endl;
			else cout << -1 << endl;
		} else cout << -1 << endl;
	}
	return 0;
}
