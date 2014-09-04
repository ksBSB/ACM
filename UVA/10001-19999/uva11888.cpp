#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
const int maxn = 200005;

int n, jump[maxn];
char s[maxn], t[maxn];

void init () {
	scanf("%s", s+1);
	n = strlen(s+1);

	for (int i = n; i; i--)
		t[i] = s[n-i+1];
	t[n+1] = '\0';
//	printf("%s\n%s\n", s+1, t+1);
}

void get_jump (char* str) {
	
	int p = 0;
	for (int i = 2; i <= n; i++) {
		while (p && str[p+1] != str[i])
			p = jump[p];

		if (str[p+1] == str[i])
			p++;
		jump[i] = p;
	}
}

int find (char* x, char* y) {
	int p = 0;
	for (int i = 1; i <= n; i++) {
		while (p && x[p+1] != y[i])
			p = jump[p];

		if (x[p+1] == y[i])
			p++;
	}
	return p;
}

int judge () {
	int ret = 0;
	set<int> vec;

	get_jump(s);
	int k = find(s, t);

	if (k == n)
		ret = 1;

	while (k) {
		vec.insert(k);
		k = jump[k];
	}

	get_jump(t);
	k = find(t, s);

	while (k) {
		if (k != n) {
			if (vec.find(n - k) != vec.end())
				return 2;
		}
		k = jump[k];
	}

	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		int k = judge();

		if (k)
			printf("%s\n", k == 2 ? "alindrome" : "palindrome");
		else
			printf("simple\n");
	}
	return 0;
}
