#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1000005;
const double eps = 1e-9;

struct state {
	int x, y;
}d[N];
int n, w, v, m, s[N];

inline void scan_d(int &ret) {  
	char c; ret = 0;  
	while((c = getchar()) < '0'|| c >'9');  
	while(c >= '0' && c <= '9') ret = ret * 10 + (c - '0'), c = getchar();  
}  

void init() {
	scanf("%d%d%d", &w, &v, &n);
	for (int i = 0; i < n; i++) scanf("%d%d", &d[i].x, &d[i].y);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) scanf("%d", &s[i]);
	sort(s, s + m);
}

bool judge(int vh) {
	double l = d[n - 1].x, r = d[n - 1].x + w;

	for (int i = n - 2; i >= 0; i--) {
		int tmp = d[i + 1].y - d[i].y;
		double ti = (double)tmp / vh;

		l -= ti *  v; r += ti * v;	

		if (d[i].x + w < l) return false;
		if (d[i].x > r) return false;

		if (d[i].x - l > eps) l = d[i].x;
		if (d[i].x + w - r < eps) r = d[i].x + w;
	}
	return true;
}

bool solve() {
	if (!judge(s[0])) return false;
	if (judge(s[m - 1])) {
		printf("%d\n", s[m - 1]);
		return true;
	}

	int l = 0, r = m;

	while (true) {

		if (r - l == 1) break;

		int mid = (l + r) / 2;

		if (judge(s[mid])) l = mid;
		else r = mid;
	}
	printf("%d\n", s[l]);
	return true;;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		if (solve() == false) printf("IMPOSSIBLE\n");
	}
	return 0;
}
