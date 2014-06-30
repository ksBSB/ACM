#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef long long ll;
ll A, B;

int solve() {
	int ans = 0;
	while (A > B) {
		A = A - (A - 1) / 2;
		ans++;
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		cin >> A >> B;
		printf("Case %d: %d\n", i, solve());
	}
	return 0;
}
