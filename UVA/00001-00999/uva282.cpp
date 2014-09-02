#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> g;
string order, a, b;

void solve () {
	cout << order << " " << a << " " << b << endl;

	for (int i = 0; i < g.size(); i++) {
		int l = 0, r = a.length() - 1;
		int gl, gr;

		for (gl = 0; gl < g[i].length(); gl++) {
			if (a[l] == g[i][gl])
				l++;
			else
				break;
		}

		for (gr = g[i].length() - 1; gr >= 0; gr--) {
			if (a[r] == g[i][gr])
				r--;
			else
				break;
		}

		if (a[l] != '*' || a[r] != '*' || gl - gr > 1)
			continue;

		cout << "mv " << g[i] << " ";
		int j;
		for (j = 0; j < b.length() && b[j] != '*'; j++)
			cout << b[j];

		for (; gl <= gr; gl++)
			cout << g[i][gl];

		for (j = j + 1; j < b.length(); j++)
			cout << b[j];
		cout << endl;
	}
}

int main () {

	while (cin >> order) {
		g.clear();

		if (order != "end") {
			g.push_back(order);
			while (cin >> order && order != "end")
				g.push_back(order);
		}

		while (cin >> order && order != "end") {
			cin >> a >> b;
			solve();
		}
		cout << endl;
	}
	return 0;
}
