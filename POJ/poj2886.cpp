#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 500005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, s;
	void set (int l, int r, int s) {
		this->l = l;
		this->r = r;
		this->s = s;
	}
}nd[maxn * 4];

const int antipri[36] = {1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,500001};
const int fact[36] = {1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200};

int N, B, v[maxn];
char name[maxn][20];

void build (int u, int l, int r) {
	nd[u].set(l, r, r - l + 1);

	if (l == r) 
		return ;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
}

int query(int u, int x) {
	nd[u].s--;

	if (nd[u].l == nd[u].r)
		return nd[u].l;

	if (nd[lson(u)].s >= x)
		return query(lson(u), x);
	else
		return query(rson(u), x - nd[lson(u)].s);
}

int bsearch (int x) {
	int l = 0, r = 35;
	for (int i = 0; i < 20; i++) {
		int mid = (l + r) / 2;
		if (antipri[mid] > x)
			r = mid;
		else
			l = mid;
	}
	return l;
}

int main () {
	while (scanf("%d%d", &N, &B) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%s%d", name[i], &v[i]);
		build(1, 1, N);

		v[0] = 0;
		int E = bsearch(N), k = 0;
		for (int i = N; i; i--) {
			B = ((B + v[k] - (v[k] > 0 ? 2 : 1)) % i + i) % i + 1;
			k = query(1, B);

			if (N - i + 1 == antipri[E]) {
				printf("%s %d\n", name[k], fact[E]);
				break;
			}
		}
	}
	return 0;
}
