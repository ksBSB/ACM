#include <cstdio>
#include <cstring>

const int N = 1e5+5;

int n, len, v[N];
char s[N], r[N];

int main () {
	for (int i = 0; i < N; i++)
		r[i] = '?';

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		len = strlen(s);
		for (int j = 0; j < len; j++) {
			if (v[j]) continue;

			if (s[j] == '?') continue;

			if (r[j] == '?')
				r[j] = s[j];
			else if (r[j] != s[j]) {
				r[j] = '?';
				v[j] = 1;
			}
		}
		r[len] = '\0';
	}

	for (int i = 0; i < len; i++) {
		if (r[i] == '?' && v[i] == 0) r[i] = 'a';
	}
	printf("%s\n", r);
	return 0;
}
