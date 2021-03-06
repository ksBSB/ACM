#include <stdio.h>
#include <string.h>

const int N = 1e6+10;

bool flag;
int n, x, s[N];

bool judge(int t) {
	int k = x*t/10;
	s[0] = x*t%10;
	for (int i = 1; i < n; i++) {
		int u = x*s[i-1] + k;
		s[i] = u%10;
		k = u/10;
	}

	if (k || s[n-1] != t || (n > 1 && s[n-2] == 0)) return false;
	flag = false;
	for (int i = n-2; i >= 0; i--) printf("%d", s[i]);
	printf("%d\n", t);
	return true;
}

int main () {
	flag = true;;
	memset(s, 0, sizeof(s));
	scanf("%d%d", &n, &x);

	for (int i = 1; i < 10; i++) 
		if (judge(i)) break;

	if (flag) printf("Impossible\n");
	return 0;
}
