#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef int ll;
const int maxn = 20005;

int n, num[maxn], s[maxn];
char str[maxn];

ll solve () {
	int tmp = num[0] = 0;
	for (int i = 1; i <= n; i++) {
		if (str[i] != '?')
			tmp ^= (1<<(str[i]-'a'));
		s[i] = num[i] = tmp;
	}

	ll ret = 0;
	sort(num, num + n + 1);

	int mv = 0;
	while (mv <= n) {

		int p = 0;
		while (p + mv <= n && num[p+mv] == num[mv])
			p++;
		ret += p * (p-1) / 2;
		mv += p;	
	}
	return ret;
}

int a[maxn], b[maxn];
ll handle (int x, int pos) {
	int A = pos, B = n + 1 - pos;

	for (int i = 0; i < pos; i++)
		a[i] = s[i];

	for (int i = pos; i <= n; i++)
		b[i-pos] = s[i]^(1<<x);

	sort(a, a + A);
	sort(b, b + B);

	ll ret = 0;
	int mva = 0, mvb = 0;
	while (mva < A && mvb < B) {
		if (a[mva] > b[mvb])
			mvb++;
		else if (a[mva] < b[mvb])
			mva++;
		else {
			int i = 0, j = 0;
			while (i + mva < A && a[i+mva] == a[mva])
				i++;
			while (j + mvb < B && b[j+mvb] == b[mvb])
				j++;

			ret += i * j;

			mva += i;
			mvb += j;
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str+1);

		n = strlen(str+1);
		int pos = -1;
		for (int i = 1; i <= n; i++) {
			if (str[i] == '?') {
				pos = i;
				break;
			}
		}
		ll ans = solve();
		if (pos != -1) {
			for (int i = 0; i + 'a' <= 'z'; i++)
				ans += handle(i, pos);
		}
		printf("%d\n", ans);
	}
	return 0;
}
