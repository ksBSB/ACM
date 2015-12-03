#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, A[maxn];

bool judge () {
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++)
			for (int k = j + 1; k < N; k++) {
				if (A[i] == A[j] + A[k]) return true;
				if (A[j] == A[i] + A[k]) return true;
				if (A[k] == A[i] + A[j]) return true;
			}
	}
	return false;
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) scanf("%d", &A[i]);
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
