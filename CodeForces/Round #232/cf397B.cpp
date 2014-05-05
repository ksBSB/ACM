#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
typedef long long ll;
ll n, l, r;

bool judge () {
	ll k = n / l;
	return r * k >= n;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		cin >> n >> l >> r;
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}
