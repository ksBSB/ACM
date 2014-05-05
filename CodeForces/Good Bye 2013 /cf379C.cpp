#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 300005;

struct state {
	int x, id;
}s[N];
int n, c[N];

bool cmp(const state& a, const state& b) {
	return a.x < b.x;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &s[i].x);
		s[i].id = i;
	}
	sort(s, s + n, cmp);
	int tmp = 0;
	for (int i = 0; i < n; i++) {
		c[s[i].id] = max(s[i].x, tmp);
		tmp = c[s[i].id] + 1;
	}
	printf("%d", c[0]);
	for (int i = 1; i < n; i++) printf(" %d", c[i]);
	printf("\n");
	return 0;
}
