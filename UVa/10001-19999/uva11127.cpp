#include <stdio.h>
#include <string.h>

const int N = 50;
int n;
char tmp[N];

bool judge(int s, int d) {
	int t = (1<<d) - 1;
	int a = s & t;
	s = s>>d;
	int b = s & t;
	s = s>>d;
	int c = s & t;
	return a == b && b == c;
}

int dfs(int s, int d) {
	int k = d / 3, t = n-d-1;
	for (int i = 1; i <= k; i++) {
		if (judge(s>>(t+1), i)) return 0;
	}

	if (d == n) {
		return 1;
	} else if (tmp[d] == '0') {
		return dfs(s, d + 1);	
	} else if (tmp[d] == '1') {
		return dfs(s+(1<<t), d + 1);
	} else {
		return dfs(s+(1<<t), d + 1) + dfs(s, d + 1);
	}
}

int main() {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		scanf("%s", tmp);
		printf("Case %d: %d\n", cas++, dfs(0, 0));
	}
	return 0;
}
