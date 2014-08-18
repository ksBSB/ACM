#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6+5;

struct state {
	int val, pos;
}sta[maxn];

bool cmp (const state& a, const state& b) {
	if (a.val != b.val)
		return a.val < b.val;
	return a.pos < b.pos;
}

int n, c[maxn], f[maxn];
ll v[maxn];

void add (int x, int val) {  
	while (x <= n) {  
		v[x] += val;  
		x += (x & (-x));  
	} 
} 

ll sum(int x) {  
	ll ans = 0;  
	while (x > 0) {  
		ans += v[x];  
		x -= (x &(-x));  
	} 
	return ans;  
}

ll solve () {
	ll ret = 0;
	memset(v, 0, sizeof(v));

	for (int i = n-1; i >= 0; i--) {
		ret += sum(c[i]-1);
		add(f[i], 1);
	}
	return ret;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &sta[i].val);
		sta[i].pos = i;
	}
	sort(sta, sta+n, cmp);

	int pre = -1, cnt = 0;
	for (int i = 0; i < n; i++) {
		if (pre != sta[i].val) {
			pre = sta[i].val;
			cnt = 1;
		} else
			cnt++;
		c[sta[i].pos] = cnt;
	}

	pre = -1, cnt = 0;
	for (int i = n; i >= 0; i--) {
		if (pre != sta[i].val) {
			pre = sta[i].val;
			cnt = 1;
		} else
			cnt++;
		f[sta[i].pos] = cnt;
	}

	printf("%lld\n", solve());
	return 0;
}
