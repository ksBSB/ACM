#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 20005;

int N, fail[maxn];
char S[maxn], T[maxn], A[maxn], B[maxn];

int miniexpress (char* s, int n) {
	int p = 0, q = 1;
	while (p < n && q < n) {
		int i;
		for (i = 0; i < n; i++)
			if (s[(p+i)%n] != s[(q+i)%n]) break;

		if (s[(p+i)%n] < s[(q+i)%n])
			p = p + i + 1;
		else 
			q = q + i + 1;
		if (p == q) q = p + 1;
	}
	return min(p, q);
}

void get(char* t, char* s, int a, int n) {
	for (int i = 0; i < n; i++)
		t[i] = s[(a+i)%n];
	t[n] = '\0';
}

bool judge(int a, int b) {
	int k = strcmp(A, B);
	if (k != 0) return k > 0;
	return a <= b;
}

void getFail (char* str, int n) {
	int p = fail[0] = fail[1] = 0;
	for (int i = 2; i <= n; i++) {
		while (p && str[p+1] != str[i]) p = fail[p];

		if (str[p+1] == str[i])
			p++;
		fail[i] = p;
	}
}

int solve (char* s, int n) {
	strcpy(T+1, s);
	getFail(T, n);

	if (n % (n - fail[n])) return n;
	else return n - fail[n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s", &N, S);

		int k = solve(S, N);

		int a = miniexpress(S, N);
		get(A, S, a, N);

		reverse(S, S + N);

		int b = miniexpress(S, N);
		get(B, S, b, N);

//		printf("%d %d!\n", a, N-b-1);
		//printf("%s %s!\n", A, B);

		a %= k;
		b = (N - b - 1) % k;

		if (judge(a, b))
			printf("%d 0\n", a + 1);
		else
			printf("%d 1\n", b + 1);
	}
	return 0;
}
