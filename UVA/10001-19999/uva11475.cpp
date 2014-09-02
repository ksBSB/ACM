#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

char s[maxn], t[maxn];
int n, jump[maxn];

void get_jump () {
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p && s[p + 1] != s[i])
			p = jump[p];

		if (s[p + 1] == s[i])
			p++;
		jump[i] = p;
	}
}

int find () {
	int p = 0;
	for (int i = 1; i <= n; i++) {
		while (p && s[p + 1] != t[i])
			p = jump[p];

		if (s[p + 1] == t[i])
			p++;
	}
	return p;
}

int main () {
	while (scanf("%s", s + 1) == 1) {
		printf("%s", s+1);
		n = strlen(s + 1);

		for (int i = 1; i <= n + 1; i++)
			t[i] = s[i];

		reverse(s + 1, s + n + 1);
		get_jump();

		int k = find();

		for (int i = k + 1; i <= n; i++)
			printf("%c", s[i]);
		printf("\n");
	}
	return 0;
}
