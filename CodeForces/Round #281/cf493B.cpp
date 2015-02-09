#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e5 + 5;
typedef long long ll;
int N, nl, nr, L[maxn], R[maxn], A[maxn];

int judge () {
	for (int i = 0; i < nl && i < nr; i++) {
		if (L[i] != R[i])
			return L[i] > R[i] ? 1 : -1;
	}
	if (nl != nr)
		return nl < nr ? 1 : -1;
	return 0;
}

int main () {

	int a;
	ll s = nl = nr = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		if (A[i] > 0)
			L[nl++] = A[i];
		else
			R[nr++] = -A[i];
		s += A[i];
	}

	if (s)
		printf("%s\n", s > 0 ? "first" : "second");
	else {
		int tmp = judge();
		if (tmp)
			printf("%s\n", tmp > 0 ? "first" : "second");
		else
			printf("%s\n", A[N-1] > 0 ? "first" : "second");
	}

	return 0;
}
