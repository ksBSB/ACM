#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6+5;

int n, jump[maxn];
char s[maxn];

void get_jump () {
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;
		jump[i] = p;
	}
}

int main () {
	while (scanf("%s", s+1) == 1 && strcmp(s+1, ".")) {
		n = strlen(s+1);
		get_jump();
		int k = n - jump[n];
		printf("%d\n", n % k == 0 ? n / k : 1);
	}
	return 0;
}
