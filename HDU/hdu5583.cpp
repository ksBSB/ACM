#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;

char str[maxn];
int L[maxn][2], R[maxn][2];

ll solve () {
	int n = strlen(str+1);
	memset(L, 0, sizeof(L));
	memset(R, 0, sizeof(R));

	for (int i = 1; i <= n; i++) {
		int d = str[i] - '0';
		L[i][d] = L[i-1][d] + 1;
	}
	for (int i = n; i; i--) {
		int d = str[i] - '0';
		R[i][d] = R[i+1][d] + 1;
	}

	ll sum = 0;
	for (int i = 1; i <= n; i++) if (str[i] != str[i+1]) {
		int d = str[i] - '0';
		sum += 1LL * L[i][d] * L[i][d];
	}

	ll ans = sum;
	for (int i = 1; i <= n; i++) {
		int t = str[i] - '0';
		ll al = i > 1 ? L[i-1][str[i-1]-'0'] : 0, am = 1, ar = i < n ? R[i+1][str[i+1]-'0'] : 0;
		ll dl = al, dm = am, dr = ar;
		if (dl && str[i-1] == str[i]) { dm += dl; dl = 0; }
		else if (al) { am += al; al = 0; }

		if (dr && str[i+1] - '0' == t) { dr += dm; dm = 0; }
		else if (ar) { ar += am; am = 0; }

		ll add = al * al + am * am + ar * ar;
		ll del = dl * dl + dm * dm + dr * dr;
		//printf("+%lld %lld %lld -%lld %lld %lld\n", al, am, ar, dl, dm, dr);
		ans = max(ans, sum + add - del);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", str+1);
		printf("Case #%d: %lld\n", kcas, solve());
	}
	return 0;
}
