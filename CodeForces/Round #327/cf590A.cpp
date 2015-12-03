#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 500005;

int N, A[maxn], T[maxn];

void draw (int l, int r) {
	int a = A[l], b = A[r];
	while (l <= r) {
		A[l++] = a;
		A[r--] = b;
	}
}

int main () {

	scanf("%d", &N);
	memset(T, 0, sizeof(T));
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);

	T[1] = T[N] = 1;
	for (int i = 2; i < N; i++)
		if (A[i] == A[i-1] || A[i] == A[i+1])
			T[i] = 1;

	int ans = 0, len = 0, pos = 0;
	for (int i = 1; i <= N; i++) {
		if (T[i]) {
			draw(pos, i);
			ans = max(ans, (len + 1) / 2);
			len = 0;
			pos = i;
		} else
			len++;
	}
	printf("%d\n", ans);
	for (int i = 1; i <= N; i++)
		printf("%d%c", A[i], i == N ? '\n' : ' ');
	return 0;
}
