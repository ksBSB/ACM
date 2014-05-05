#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

const int N = 20;

struct state {
	int k, v;
	friend bool operator < (const state& a, const state& b) {
		return a.k < b.k;
	}
};

int n, s, t[8];
set<state> rec;
char str[N];

void init() {
	rec.clear();
	char cha[N];

	scanf("%s", str);
	for (int i = 0; i < 8; i++) {
		scanf("%s", cha);
		int sum = 0;
		for (int j = 0; j < 3; j++) 
			sum = cha[j] - 'a' + sum * 2;
		t[sum] = cha[3] - 'a';
	}
	scanf("%d", &s);
}

int judge(char* a, char* b, int p, int& q) {
	int sum;
	for (int i = 0; i < n; i++) {
		sum = (a[i] - 'a') * 4 + (a[(i+2)%n] - 'a') * 2 + a[(i+3)%n] - 'a';
		b[(i+2)%n] = t[sum] + 'a';
	}
	b[n] = '\0';

	sum = 0;
	for (int i = 0; i < n; i++) sum = sum * 2 + b[i] - 'a';
	state u;
	u.k = sum; u.v = p;

	set<state>::iterator it = rec.find(u);
	if (it != rec.end()) {
		q = it->v;
		return p - q;
	} else {
		rec.insert(u);
		return 0;
	}
}

void solve() {
	int cnt, q = 0;
	bool flag = false;
	char tmp[N];
	for (int i = 0; i < n; i++) q = q * 2 + str[i] - 'a';
	state u; u.k = q; u.v = 0;
	rec.insert(u);

	for (int i = 1; i <= s; i++) {
		cnt = judge(str, tmp, i, q);
		if (cnt) {
			cnt = (s-q) % cnt;
			flag = true;
			break;
		}
		strcpy(str, tmp);
	}

	if (flag) {
		cnt += q;

		for (set<state>::iterator i = rec.begin(); i != rec.end(); i++) {
			if (i->v == cnt) {
				cnt = i->k; break;
			}
		}

		for (int i = n-1; i >= 0; i--) {
			tmp[i] = 'a' + cnt % 2;
			cnt /= 2;
		}
	}

	char ans[N];
	strcpy(ans, tmp);
	strcpy(str, tmp);	

	for (int i = 0; i < n; i++) {
		tmp[0] = str[n-1];
		strncpy(tmp+1, str, n-1);
		if (strcmp(ans, tmp) > 0) strcpy(ans, tmp);
		strcpy(str, tmp);
	}
	printf("%s\n", ans);
}

int main() {
	while (scanf("%d%*c", &n) == 1) {
		init();
		solve();
	}
	return 0;
}
