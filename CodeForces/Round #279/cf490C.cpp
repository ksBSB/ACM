#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;

int N, A, B, l[maxn], r[maxn], t[maxn];
char s[maxn];

int solve () {
	t[0] = 1;
	for (int i = 1; i <= N; i++)
		t[i] = t[i-1] * 10 % B;

	for (int i = 0; i < N; i++)
		l[i] = (l[i-1] * 10 + (s[i] - '0')) % A;

	int tmp = 0;
	for (int i = N - 1; i; i--) {
		tmp = (tmp + (s[i] - '0') * t[N-i-1]) % B;
		if (s[i] == '0')
			continue;
		if (tmp == 0 && l[i-1] == 0)
			return i;
	}
	return 0;
}

int main () {
	scanf("%s%d%d", s, &A, &B);
	N = strlen(s);
	int ans = solve();

	if (ans) {
		printf("YES\n");
		for (int i = 0; i < ans; i++)
			printf("%c", s[i]);
		printf("\n");
		for (int i = ans; i < N; i++)
			printf("%c", s[i]);
		printf("\n");
	} else
		printf("NO\n");

	return 0;
}
