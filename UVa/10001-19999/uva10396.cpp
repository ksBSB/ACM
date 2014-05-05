#include <stdio.h>
#include <string.h>
#include <set>
#include <algorithm>

using namespace std;

const int N = 6;
const int tmp[N] = {0, 1, 10, 100, 1000, 10000};
int n, rec[N];
set<int> v[N];

bool judge(int a, int b) {
	int c[10], s = a * b;
	memset(c, 0, sizeof(c));
	while (a) {
		c[a%10]++; a /= 10;
	}
	while (b) {
		c[b%10]++; b /= 10;
	}
	while (s) {
		c[s%10]--; s /= 10;
	}
	for (int i = 0; i < 10; i++) if (c[i] != 0) return false;
	return true;
}

void solve() {
	int k = n / 2;
	if (rec[k] == 0) {
		for (int i = tmp[k]; i < tmp[k+1]; i++) {
			for (int j = i; j < tmp[k+1]; j++) {
				if (i % 10 == 0 && j % 10 == 0) continue;
				if (i % 2 && j % 2) continue;
				if (judge(i, j)) v[k].insert(i * j);
			}
		}
	}
	rec[k] = 1;
	for (set<int>::iterator i = v[k].begin(); i != v[k].end(); i++)
		printf("%d\n", *i);
	printf("\n");
}

int main() {
	memset(rec, 0, sizeof(rec));
	while (scanf("%d", &n) == 1) {
		solve();
	}
	return 0;
}
