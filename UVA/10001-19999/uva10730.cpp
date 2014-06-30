#include <stdio.h>
#include <string.h>

const int N = 10005;

int n, v[N];

void init() {
	int a;
	char ch = getchar();
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		v[a] = i;
	}
}

bool judge() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i] >= v[j] || 2*j-i < 0) continue;
			if (2*j-i >= n) break;
			if (v[2*j - i] <= v[j]) continue;
			return true;
		}
	}
	return false;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("%s\n", judge() ? "no" : "yes");
	}
	return 0;
}
