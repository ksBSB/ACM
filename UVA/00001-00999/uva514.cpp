#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, arr[maxn];

bool judge () {
	for (int i = 1; i < N - 1; i++) {
		if (arr[i-1] > arr[i+1] && arr[i+1] > arr[i])
			return false;
	}
	return true;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		while (scanf("%d", &arr[0]) && arr[0]) {
			for (int i = 1; i < N; i++)
				scanf("%d", &arr[i]);
			printf("%s\n", judge() ? "Yes" : "No");
		}
		printf("\n");
	}
	return 0;
}
