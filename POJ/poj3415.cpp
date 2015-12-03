#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn = 2 * 1e5 + 5;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[305];

	int d[maxn][20];

	void init(char* str, int len);
	void build(int m);
	void get_height();

	ll get(int l, int r, int k, int p);
	ll solve(int k, int p);
}SFA;

int K;
char a[maxn], b[maxn];

int main () {
	while (scanf("%d", &K) == 1 && K) {
		scanf("%s%s", a, b);
		int na = strlen(a), nb = strlen(b);
		a[na] = 1;
		for (int i = 0; i <= nb; i++) a[na + i + 1] = b[i];
		SFA.init(a, na + nb + 1);
		printf("%lld\n", SFA.solve(K, na));
	}
	return 0;
}

void Suffix_Arr::init(char* str, int len) {
	n = 0;
	for (int i = 0; i < len; i++)
		s[n++] = str[i];
	s[n++] = 0;
}

ll Suffix_Arr::get(int l, int r, int k, int p) {
	ll ret = 0;

	ll sum = 0;
	stack<pii> st;

	for (int i = l; i <= r; i++) {
		pii u = make_pair(height[i], 0);
		while (!st.empty() && st.top().first >= u.first) {
			pii v = st.top(); st.pop();
			sum -= 1LL * (v.first - k + 1) * v.second;
			u.second += v.second;
		}
		sum += 1LL * (u.first - k + 1) * u.second;
		st.push(u);
		if (SA[i] < p) {
			st.push(make_pair(n, 1));
			sum += 1LL * (n - k + 1);
		} else
			ret += sum;
	}

	sum = 0;
	while (!st.empty()) st.pop();

	for (int i = l; i <= r; i++) {
		pii u = make_pair(height[i], 0);
		while (!st.empty() && st.top().first >= u.first) {
			pii v = st.top(); st.pop();
			sum -= 1LL * (v.first - k + 1) * v.second;
			u.second += v.second;
		}
		sum += 1LL * (u.first - k + 1) * u.second;
		st.push(u);
		if (SA[i] > p) {
			st.push(make_pair(n, 1));
			sum += 1LL * (n - k + 1);
		} else
			ret += sum;
	}

	//printf("%d %d %lld\n", l, r, ret);
	return ret;
}

ll Suffix_Arr::solve(int k, int p) {
	build(300);
	get_height();

	ll ret = 0;
	int l = 0, r = 0;

	/*
	for (int i = 0; i < n; i++) printf("%3d ", height[i]);
	printf("\n");
	for (int i = 0; i < n; i++) printf("%3d ", SA[i]);
	printf("\n");
	*/

	while (l < n) {
		r = l + 1;
		while (r < n && height[r] >= k) r++;
		ret += get(l, r-1, k, p);
		l = r;
	}
	/*
	*/
	return ret;
}


void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;
	int mv = height[0] = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i]-1];
		while (s[i+mv] == s[j+mv]) mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build(int m) {
	int* x = tmp_one, *y = tmp_two;

	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i-1];
	for (int i = n - 1; i >= 0; i--) SA[--c[x[i]]] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int mv = 0;
		for (int i = n - k; i < n; i++) y[mv++] = i;
		for (int i = 0; i < n; i++) if(SA[i] >= k) 
			y[mv++] = SA[i] - k;

		for (int i = 0; i < m; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[x[y[i]]]++;
		for (int i = 1; i < m; i++) c[i] += c[i-1];
		for (int i = n - 1; i >= 0; i--) SA[--c[x[y[i]]]] = y[i];

		swap(x, y);
		mv = 1;
		x[SA[0]] = 0;

		for (int i = 1; i < n; i++)
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && y[SA[i-1] + k] == y[SA[i] + k] ? mv - 1 : mv++);

		if (mv >= n) break;
		m = mv;
	}
}

/*
int Suffix_Arr::rmq_query(int x, int y) {
	if (x == y) return d[x][0];
	if (x > y) swap(x, y);

	x++;
	int k = 0;
	while ((1<<(k+1)) <= y - x + 1) k++;
	return min(d[x][k], d[y-(1<<k)+1][k]);
}
void Suffix_Arr::rmq_init() {
	for (int i = 0; i < n; i++) d[i][0] = height[i];

	for (int k = 1; (1<<k) <= n; k++) {
		for (int i = 0; i + (1<<k) - 1 < n; i++)
			d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
	}
}

*/

