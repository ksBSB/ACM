#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N;
char S[maxn], T[maxn], F[maxn];

int miniexpress(char* s) {
	int p = 0, q = 1;
	while (p < N && q < N) {
		int i;
		for (i = 0; i <	N; i++) {
			if (s[(p+i)%N] != s[(q+i)%N])
				break;
		}

		if (s[(p+i)%N] > s[(q+i)%N])
			p = p + i + 1;
		else
			q = q + i + 1;

		if (p == q)
			q++;
	}
	return min(p, q) + 1;
}

void solve () {
	char tmp[maxn];
	memset(tmp, 0, sizeof(tmp));
	int pos = miniexpress(T) - 1;

	for (int i = 0; i < N; i++)
		tmp[i] = T[(pos + i) % N];
	if (strcmp(F, tmp) > 0)
		strcpy(F, tmp);
}

int main () {
	scanf("%d%s", &N, S);
	strcpy(F, S);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < N; j++)
			T[j] = '0' + (S[j] - '0' + i) % 10;
		solve();
	}
	printf("%s\n", F);
	return 0;
}
