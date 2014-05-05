#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;
const int N = 105;

int n, k[N], ans;
map<int, int> g;

int bitCount(int x) {
	return x == 0 ? 0 : bitCount(x >> 1) + (x&1);
}

int handle(char* s) {
	int len = strlen(s), k = 0;
	for (int i = 0; i < len; i++)
		k ^= (1<<(s[i]-'A'));
	return k;
}

void init () {
	ans = 0;
	g.clear();

	char word[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		k[i] = handle(word);
	}
}

void solve () {
	int mid = n >> 1;
	for (int i = 0; i < (1<<mid); i++) {
		int s = 0;	
		for (int j = 0; j < mid; j++) if (i & (1<<j)) {
			s ^= k[j];
		}

		if (!g[s] || bitCount(g[s]) < bitCount(i)) g[s] = i;
	}

	int t = n - mid;
	for (int i = 0; i < (1<<t); i++) {
		int s = 0;
		for (int j = 0; j < t; j++) if (i & (1<<j)) {
			s ^= k[mid + j];
		}

		if (g[s] && bitCount(g[s]) + bitCount(i) > bitCount(ans)) {
			ans = (i<<mid) ^ g[s];
		}
	}
}

void put () {
	int x = 0;
	printf("%d\n", bitCount(ans));
	for (int i = 0; i < n; i++) if (ans & (1<<i)) {
		if (x++) printf(" ");
		printf("%d", i + 1);
	}
	printf("\n");
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		solve();
		put();
	}
	return 0;
}
