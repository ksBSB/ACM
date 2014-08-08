#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxl = 20;

int N, A[10], B[10];

inline int bitcount (int x) {
	return x == 0 ? 0 : bitcount(x>>1) + (x&1);
}

inline int change (char ch) {
	if (ch >= '3' && ch <= '9')
		return ch - '0';
	switch (ch) {
		case 'T':
			return 10;
		case 'J':
			return 11;
		case 'Q':
			return 12;
		case 'K':
			return 13;
		case 'A':
			return 14;
		case '2':
			return 15;
		case 'X':
			return 16;
		case 'Y':
			return 17;
	}
	return -1;
}

int get (char* str, int n, int s, int& v) {
	int bit = bitcount(s);
	if (bit > 6)
		return 0;

	int c[maxl], type = 0;
	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; i++) {
		if (s&(1<<i)) {
			int tmp = change(str[i]);
			++c[tmp];

			if (c[tmp] > type || (c[tmp] == type && tmp > v)) {
				type = c[tmp];
				v = tmp;
			}
		}
	}

	// 王炸;
	if (c[17] && c[16] && bit == 2) {
		v = 17;
		return 7;
	}

	// 炸弹;
	if (type == 4 && bit == 4)
		return 7;

	// 4带2;
	if (type == 4 && bit == 6)
		return 6;

	// 3带1;
	if (type == 3 && bit == 4)
		return 4;

	// 3;
	if (type == 3 && bit == 3)
		return 3;

	// 对;
	if (type == 2 && bit == 2)
		return 2;

	// 单;
	if (type == 1 && bit == 1)
		return 1;

	// 3带2;
	if (type == 3 && bit == 5) {
		for (int i = 3; i <= 17; i++)
			if (c[i] == 2)
				return 5;
	}
	return 0;
}

void solve (char* s, int* t) {
	int n = strlen(s), v;

	for (int i = 1; i < (1<<n); i++) {
		v = 0;
		int k = get(s, n, i, v);
		t[k] = max(t[k], v);
	}
}

bool judge () {

	if (N <= 6 && A[N])
		return true;

	if (N == 4 && A[7])
		return true;

	if (A[7] && B[7])
		return A[7] > B[7];

	if (B[7])
		return false;

	for (int i = 1; i <= 7; i++) {
		if (A[i] && A[i] >= B[i])
			return true;
	}
	return false;
}

void init () {
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));

	char a[maxl], b[maxl];
	scanf("%s%s", a, b);
	solve(a, A);
	solve(b, B);
	N = strlen(a);
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		init();
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}
