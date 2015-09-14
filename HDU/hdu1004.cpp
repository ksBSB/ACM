#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N;
map<string, int> G;

int main () {
	while (scanf("%d", &N) == 1 && N) {
		G.clear();
		int cnt = 0;
		string ans, tmp;

		for (int i = 0; i < N; i++) {
			cin >> tmp;
			int x = ++G[tmp];
			if(x > cnt) {
				cnt = x;
				ans = tmp;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
