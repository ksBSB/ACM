#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 105;

int Arr[2][2], fac[2][maxn], cnt[2][2];

void divFact(int* a, int* b, int& c, int n) {
	while (n % 2 == 0) {
		b[0]++;
		n /= 2;
	}
	while (n % 3 == 0) {
		b[1]++;
		n /= 3;
	}

	int m = sqrt(n);
	for (int i = 5; i <= m; i++) {
		while (n % i == 0) {
			a[++c] = i;
			n /= i;
		}
		if (n < i)
			break;
	}

	if (n != 1)
		a[++c] = n;
}

void del (int idx, int d, int n) {
	while (n && Arr[idx][0] % d == 0) {
		Arr[idx][0] /= d;
		if (d == 3)
			Arr[idx][0] *= 2;
		n--;
	}
	while (n && Arr[idx][1] % d == 0) {
		Arr[idx][1] /= d;
		if (d == 3)
			Arr[idx][1] *= 2;
		n--;
	}
}

int solve () {
	if (fac[0][0] != fac[1][0])
		return -1;
	for (int i = 1; i <= fac[0][0]; i++) {
		if (fac[0][i] != fac[1][i])
			return -1;
	}
	int ret = 0, n;

	if (cnt[0][1] >= cnt[1][1]) {
		n = cnt[0][1] - cnt[1][1];
		cnt[0][0] += n;
		del(0, 3, n);
	} else {
		n = cnt[1][1] - cnt[0][1];
		cnt[1][0] += n;
		del(1, 3, n);
	}
	ret += n;
	n = cnt[0][0] - cnt[1][0];

	if (n >= 0) {
		ret += n;
		del(0, 2, n);
	} else {
		ret -= n;
		del(1, 2, -n);
	}
	return ret;
}

int main () {
	for (int i = 0; i < 2; i++) {
		fac[i][0] = 0;
		for (int j = 0; j < 2; j++) {
			scanf("%d", &Arr[i][j]);
			divFact(fac[i], cnt[i], fac[i][0], Arr[i][j]);
		}
		sort(fac[i] + 1, fac[i] + fac[i][0] + 1);
	}

	int ans = solve();

	if(ans >= 0) {
		printf("%d\n", ans);
		for (int i = 0; i < 2; i++)
			printf("%d %d\n", Arr[i][0], Arr[i][1]);
	} else
		printf("-1\n");
	return 0;
}
